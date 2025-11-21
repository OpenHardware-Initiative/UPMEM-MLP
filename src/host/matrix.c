#include <assert.h>
#include <dpu.h>
#include <dpu_log.h>
#include "mlp.h"
#include "upmem.h"

struct dpu_set_t dpus, dpu;

void multiply_matrix(const double *A, const double *B, double *C, int rows_a, int cols_a, int cols_b)
{
#ifdef UPMEM
    multiply_matrix_upmem(A, B, C, rows_a, cols_a, cols_b);
#else
    multiply_matrix_naive(A, B, C, rows_a, cols_a, cols_b);
#endif
}

void multiply_matrix_upmem(const double *A, const double *B, double *C, int rows_a, int cols_a, int cols_b)
{
    assert(TILE_SIZE / NUM_DPU <= ROWS_A_PER_DPU_MAX);

    double tileA[TILE_SIZE][TILE_SIZE];
    double tileB[TILE_SIZE][TILE_SIZE];
    double tileC[TILE_SIZE][TILE_SIZE];

    for(int i=0; i<rows_a; ++i) {
        for(int j=0; j<cols_b; ++j) {
            C[i * cols_b + j] = 0;
        }
    }

    DPU_ASSERT(dpu_alloc(NUM_DPU, NULL, &dpus));
    DPU_ASSERT(dpu_load(dpus, DPU_BINARY_PATH, NULL));

    for(int ii=0; ii<rows_a; ii+=TILE_SIZE) {
        for(int jj=0; jj<cols_b; jj+=TILE_SIZE) {
            for(int kk=0; kk<cols_a; kk+=TILE_SIZE) {
    
                for(int i=0; i<TILE_SIZE; ++i) {
                    for(int j=0; j<TILE_SIZE; ++j) {
                        if(ii + i < rows_a && kk + j < cols_a) {
                            tileA[i][j] = A[(ii + i) * cols_a + (kk + j)];
                        } else {
                            tileA[i][j] = 0;
                        }
    
                        if(kk + i < cols_a && jj + j < cols_b) {
                            tileB[i][j] = B[(kk + i) * cols_b + (jj + j)];
                        } else {
                            tileB[i][j] = 0;
                        }
                    }
                }
    
                process_tile_upmem(&tileA[0][0], &tileB[0][0], &tileC[0][0], TILE_SIZE, TILE_SIZE, TILE_SIZE);
    
                for(int row=0; row<TILE_SIZE; row++) {
                    for(int col=0; col<TILE_SIZE; col++) {
                        if(ii + row<rows_a && jj + col<cols_b) {
                            C[(ii + row) * cols_b + (jj + col)] += tileC[row][col];
                        }
                    }
                }
            }
        }
    }

    DPU_ASSERT(dpu_free(dpus));
}

void multiply_matrix_naive(const double *A, const double *B, double *C, int rows_a, int cols_a, int cols_b)
{
    for(int i=0; i<rows_a; i++) {
        for(int j=0; j<cols_b; j++) {
            double sum = 0.0;
            for(int k=0; k<cols_a; k++) {
                sum += A[i*cols_a+k] * B[k*cols_b+j];
            }
            C[i*cols_b+j] = sum;
        }
    }
}

void process_tile_upmem(const double *A, const double *B, double *C, int rows_a, int cols_a, int cols_b)
{
    assert(rows_a <= ROWS_A_MAX);
    assert(cols_a <= COLS_A_MAX);
    assert(cols_b <= COLS_B_MAX);
    
    unsigned int bytes_b = cols_a * cols_b * sizeof(double);
    DPU_ASSERT(dpu_broadcast_to(dpus, "B_whole", 0, B, bytes_b, DPU_XFER_DEFAULT));

    uint32_t dpu_rows_a_max = (rows_a + NUM_DPU - 1) / NUM_DPU;

    uint32_t dpu_idx = 0;
    DPU_FOREACH(dpus, dpu) {

        uint32_t row_start = dpu_idx * dpu_rows_a_max;
        uint32_t dpu_rows_a_actual = (row_start >= rows_a) ? 0
                                   : (dpu_rows_a_max > rows_a - row_start) ? (rows_a - row_start)
                                   : dpu_rows_a_max;

        dpu_args_t args = {
            .rows_a = dpu_rows_a_actual,
            .cols_a = cols_a,
            .cols_b = cols_b
        };

        DPU_ASSERT(dpu_copy_to(dpu, "DPU_INPUT_ARGS", 0, &args, sizeof(args)));

        if(dpu_rows_a_actual) {
            uint32_t elems_a = dpu_rows_a_actual * cols_a;
            uint32_t bytes_a = elems_a * sizeof(double);

            double *A_chunk = (double*)malloc(bytes_a);

            for(int r=0; r<dpu_rows_a_actual; ++r) {
                unsigned int global_row = row_start + r;
                memcpy(&A_chunk[r*cols_a], &A[global_row*cols_a], cols_a*sizeof(double));
            }

            DPU_ASSERT(dpu_copy_to(dpu, "A_chunk", 0, A_chunk, bytes_a));
            free(A_chunk);
        }

        dpu_idx++;
    }

    DPU_ASSERT(dpu_launch(dpus, DPU_SYNCHRONOUS));

    dpu_idx = 0;
    DPU_FOREACH(dpus, dpu) {
        
        uint32_t row_start = dpu_idx * dpu_rows_a_max;
        uint32_t dpu_rows_a_actual = (row_start >= rows_a) ? 0
                                   : (dpu_rows_a_max > rows_a - row_start) ? (rows_a - row_start)
                                   : dpu_rows_a_max;

        if(dpu_rows_a_actual) {
            uint32_t elems_c = dpu_rows_a_actual * cols_b;
            uint32_t bytes_c = elems_c * sizeof(double);

            double *C_chunk = (double*)malloc(bytes_c);

            DPU_ASSERT(dpu_copy_from(dpu, "C_chunk", 0, C_chunk, bytes_c));

            for(int r=0; r<dpu_rows_a_actual; ++r) {
                unsigned int global_row = row_start + r;
                memcpy(&C[global_row * cols_b], &C_chunk[r * cols_b], cols_b*sizeof(double));
            }

            free(C_chunk);
        }

        dpu_idx++;
    }
}

void transpose_matrix(const double* A, double *C, int rows, int cols)
{
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            C[j*rows+i] = A[i*cols+j];
        }
    }
}

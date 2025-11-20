#include "mlp.h"

void multiply_matrix(const double *A, const double *B, double *C, int rows_a, int cols_a, int cols_b)
{
    double tileA[TILE_SIZE][TILE_SIZE];
    double tileB[TILE_SIZE][TILE_SIZE];
    double tileC[TILE_SIZE][TILE_SIZE];

    for(int i=0; i<rows_a; ++i) {
        for(int j=0; j<cols_b; ++j) {
            C[i * cols_b + j] = 0;
        }
    }

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
    
                multiply_matrix_naive(&tileA[0][0], &tileB[0][0], &tileC[0][0], TILE_SIZE, TILE_SIZE, TILE_SIZE);
    
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

void transpose_matrix(const double* A, double *C, int rows, int cols)
{
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            C[j*rows+i] = A[i*cols+j];
        }
    }
}

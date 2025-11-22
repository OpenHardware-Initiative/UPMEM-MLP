#include "mlp.h"
#include "upmem.h"

void multiply_matrix(const double *A, const double *B, double *C, int rows_a, int cols_a, int cols_b)
{
#ifdef UPMEM
    init_dpus();
    multiply_matrix_upmem(A, B, C, rows_a, cols_a, cols_b);
#else
    multiply_matrix_naive(A, B, C, rows_a, cols_a, cols_b);
#endif
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

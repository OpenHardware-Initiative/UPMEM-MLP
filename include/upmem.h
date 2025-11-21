#ifndef UPMEM_H
#define UPMEM_H

#include <stdint.h>

#define ROWS_A_MAX 96
#define COLS_A_MAX 96
#define COLS_B_MAX 96
#define ROWS_A_PER_DPU_MAX 16

#define NUM_DPU 16

typedef struct {
    uint32_t rows_a;
    uint32_t cols_a;
    uint32_t cols_b;
} dpu_args_t;

void multiply_matrix_upmem(const double *A, const double *B, double *C, int rows_a, int cols_a, int cols_b);

#endif

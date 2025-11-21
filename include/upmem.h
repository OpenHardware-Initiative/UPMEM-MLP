#ifndef UPMEM_H
#define UPMEM_H

#include <stdint.h>

#define ROWS_A_MAX 320
#define COLS_A_MAX 320
#define COLS_B_MAX 320

#ifndef DPU_BINARY_PATH
#define DPU_BINARY_PATH "build/dpu_program"
#endif

#ifndef NUM_DPU
#define NUM_DPU 64
#endif

#ifndef TILE_SIZE
#define TILE_SIZE 128
#endif

#define ROWS_A_PER_DPU_MAX ((ROWS_A_MAX + NUM_DPU - 1) / NUM_DPU)

typedef struct {
    uint32_t rows_a;
    uint32_t cols_a;
    uint32_t cols_b;
} dpu_args_t;

void multiply_matrix_upmem(const double *A, const double *B, double *C, int rows_a, int cols_a, int cols_b);
void process_tile_upmem(const double *A, const double *B, double *C, int rows_a, int cols_a, int cols_b);

#endif

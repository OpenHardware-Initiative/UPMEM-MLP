#ifndef UPMEM_H
#define UPMEM_H

#include <stdint.h>

#ifndef DPU_BINARY_PATH
#define DPU_BINARY_PATH "build/dpu_program"
#endif

#ifndef NUM_DPU
#define NUM_DPU 32
#endif

#ifndef TILE_SIZE
#define TILE_SIZE 512
#endif

#define EVAL_DPU_CC 458000000

typedef struct {
    uint32_t rows_a;
    uint32_t cols_a;
    uint32_t cols_b;
} dpu_args_t;

extern int upmem_initialized;

void free_dpus();
void init_dpus();
void multiply_matrix_upmem(const float *A, const float *B, float *C, int rows_a, int cols_a, int cols_b);
void process_tile_upmem(const float *A, const float *B, float *C, int rows_a, int cols_a, int cols_b);

#endif

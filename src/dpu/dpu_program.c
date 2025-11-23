#include <mram.h>
#include <defs.h>
#include <perfcounter.h>
#include <stdio.h>
#include "upmem.h"

__mram_noinit float A_chunk[TILE_SIZE * TILE_SIZE];
__mram_noinit float B_whole[TILE_SIZE * TILE_SIZE];
__mram_noinit float C_chunk[TILE_SIZE * TILE_SIZE];

__host dpu_args_t DPU_INPUT_ARGS;

int main()
{
    perfcounter_config(COUNT_CYCLES, false);

    dpu_args_t dpu_input_args = DPU_INPUT_ARGS;
    uint32_t rows_a = dpu_input_args.rows_a;
    uint32_t cols_a = dpu_input_args.cols_a;
    uint32_t cols_b = dpu_input_args.cols_b;
    
    if(!rows_a)
        return 0;

    perfcounter_t cc_start = perfcounter_get();

    int chunk = rows_a / NR_TASKLETS;
    int row_start = chunk * me();

    for(int i=row_start; i<(row_start+chunk); ++i) {
        for(int j=0; j<cols_b; ++j) {
            float sum = 0;
            for(int k=0; k<cols_a; ++k) {
                sum += A_chunk[i * cols_a + k] * B_whole[k * cols_b + j];
            }
            C_chunk[i * cols_b + j] = sum;
        }
    }

    perfcounter_t cc_end = perfcounter_get();

    if(me() == 0)
        printf("DPU completed in %ld cycles\n", cc_end-cc_start);
    
    return 0;
}
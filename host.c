#include <assert.h>
#include <dpu.h>
#include <dpu_log.h>
#include <stdio.h>
#include <string.h>

#define DPU_NR 16

int main(void)
{
    struct dpu_set_t set, dpu;

    char binary[100];

    DPU_ASSERT(dpu_alloc(16, NULL, &set));

    int i = 0;
    DPU_FOREACH(set, dpu) {
        char prefix [] = "./dpu/dpu";
        char suffix [] = "/matmul.o";
        snprintf(binary, sizeof(binary), "%s%d", prefix, i);
        strcat(binary, suffix);
        DPU_ASSERT(dpu_load(dpu, binary, NULL));
        i++;
    }
    
    DPU_ASSERT(dpu_launch(set, DPU_SYNCHRONOUS));

    DPU_FOREACH(set, dpu) {
        DPU_ASSERT(dpu_log_read(dpu, stdout));
    }

    DPU_ASSERT(dpu_free(set));

    return 0;
}
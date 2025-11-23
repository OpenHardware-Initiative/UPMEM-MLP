DPU_UPMEM_CLANG = dpu-upmem-dpurte-clang
DPU_UPMEM_CFLAGS += -DNR_TASKLETS=16

BATCH_SIZE ?= 20
MAX_EPOCH ?= 10
NUM_TRAIN_SAMPLES ?= 200

CFLAGS += -std=c99 -Iinclude -D_GNU_SOURCE -DVERBOSE -DDEBUG
CFLAGS += -DBATCH_SIZE=$(BATCH_SIZE) -DMAX_EPOCH=$(MAX_EPOCH) -DNUM_TRAIN_SAMPLES=$(NUM_TRAIN_SAMPLES)

BUILD_DIR = build/

UPMEM ?= 1
ifeq ($(UPMEM), 1)
	CFLAGS += -DUPMEM
endif

SAN ?= 0
ifeq ($(SAN), 1)
	CFLAGS += -fsanitize=address,undefined,leak -fno-omit-frame-pointer -g
endif

all: clean
	mkdir $(BUILD_DIR); \
	$(DPU_UPMEM_CLANG) $(DPU_UPMEM_CFLAGS) -Iinclude -o build/dpu_program src/dpu/dpu_program.c; \
	gcc src/host/*.c $(CFLAGS) -o build/mlp -lm `dpu-pkg-config --cflags --libs dpu`

clean:
	rm -rf $(BUILD_DIR)

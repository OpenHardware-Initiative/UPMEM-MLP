DPU_UPMEM_CLANG = dpu-upmem-dpurte-clang
DPU_UPMEM_CFLAGS += 
FILES_TO_DELETE = build/

all: clean
	mkdir build; \
	$(DPU_UPMEM_CLANG) $(DPU_UPMEM_CFLAGS) -Iinclude -o build/dpu_program src/dpu/dpu_program.c; \
	gcc -std=c99 -O0 -Iinclude src/host/*.c -D_GNU_SOURCE -DVERBOSE -DDEBUG -DBATCH_SIZE=2 -DMAX_EPOCH=8 -DNUM_TRAIN_SAMPLES=40 -o build/mlp -lm `dpu-pkg-config --cflags --libs dpu`

clean:
	rm -rf $(FILES_TO_DELETE)

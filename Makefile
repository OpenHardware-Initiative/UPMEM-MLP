CLANG = dpu-upmem-dpurte-clang
SOURCE = matmul
CFLAGS += -O0 -DNR_TASKLETS=6
FILESTODELETE = matmul.c dpu/

all:
	python3 generate.py && \
	for test in $$(seq 0 15); do \
		$(CLANG) $(CFLAGS) -o dpu/dpu$$test/${SOURCE}.o dpu/dpu$$test/${SOURCE}.c; \
	done

clean:
	rm -rf *.o ${FILESTODELETE}

clean_all:
	rm -rf *.o .vscode/ .cache/ .__pycache__/ 
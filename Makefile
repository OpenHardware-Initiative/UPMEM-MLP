CLANG = dpu-upmem-dpurte-clang
SOURCE = matmul
CFLAGS += -O0
FILESTODELETE = matmul.c

all:
	python3 generate.py && \
	${CLANG} ${CFLAGS} -o ${SOURCE}.o ${SOURCE}.c

clean:
	rm -rf *.o ${FILESTODELETE}

clean_all:
	rm -rf *.o .vscode/ .cache/ .__pycache__/
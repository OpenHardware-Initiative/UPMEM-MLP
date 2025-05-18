CLANG = dpu-upmem-dpurte-clang
SOURCE = matmul
CFLAGS += -O0

all: 
	${CLANG} ${CFLAGS} -o ${SOURCE}.o ${SOURCE}.c

clean:
	rm -rf *.o

clean_all:
	rm -rf *.o .vscode/ .cache/ .__pycache__/
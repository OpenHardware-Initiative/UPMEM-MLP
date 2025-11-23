import os
import random

matrixa_dims = (96, 96)
matrixb_dims = (96, 96)

num_dpu_used = 16

template_name   = 'matrices.template'
target_dir      = 'dpu/dpu{dpu}'
targetc_name    = 'matmul.c'
targeth_name    = 'matrices.h'

def generateRandomMatrix(row, col):
    mat = []
    for r in range(row):
        for c in range(col):
            mat.append(random.randint(0, 31))   # I picked these numbers arbitrarily
    return mat

def main():

    for row in range(num_dpu_used):
        with open(template_name, mode='r') as tempfile:
            template = tempfile.read()

        if(matrixa_dims[1] != matrixb_dims[0]):
            raise ValueError('First matrix\' row count has to be equal to second matrix\' column count.')
        
        tempfilled = template.format(
                                    matrixa_rowcount=matrixa_dims[0]//num_dpu_used,
                                    matrixa_colcount=matrixa_dims[1],
                                    matrixb_rowcount=matrixb_dims[0],
                                    matrixb_colcount=matrixb_dims[1],
                                    dpu_nr = row,
                                    mat1=', '.join(map(str, generateRandomMatrix(matrixa_dims[0]//num_dpu_used, matrixa_dims[1]))),
                                    mat2=', '.join(map(str, generateRandomMatrix(matrixa_dims[0], matrixa_dims[1])))
        )

        target_dpu_dir = target_dir.format(dpu=row)

        os.makedirs(target_dpu_dir, exist_ok=True)

        with open(f'{target_dpu_dir}/{targeth_name}', mode='w') as cfile:
            cfile.write(tempfilled)
    
        with open('matmul.template', mode='r') as matmulfile:
            template = matmulfile.read()

        with open(f'{target_dpu_dir}/{targetc_name}', mode='w') as matmulfile:
            matmulfile.write(template)


if __name__ == '__main__':
    main()
import random

matrixa_dims = (32, 32)
matrixb_dims = (32, 32)

template_name = 'matmul.template'
targetfile_name = 'matmul.c'

def generateRandomMatrix(row, col):
    mat = []
    for r in range(row):
        for c in range(col):
            mat.append(random.randint(0, 31))   # I picked these numbers arbitrarily
    return mat

def main():

    with open(template_name, mode='r') as tempfile:
        template = tempfile.read()

    if(matrixa_dims[1] != matrixb_dims[0]):
        raise ValueError('First matrix\' row count has to be equal to second matrix\' column count.')
    
    tempfilled = template.format(
                                matrixa_rowcount=matrixa_dims[0],
                                matrixa_colcount=matrixa_dims[1],
                                matrixb_rowcount=matrixb_dims[0],
                                matrixb_colcount=matrixb_dims[1],
                                mat1=', '.join(map(str, generateRandomMatrix(matrixa_dims[0], matrixa_dims[1]))),
                                mat2=', '.join(map(str, generateRandomMatrix(matrixa_dims[0], matrixa_dims[1])))
    )

    with open(targetfile_name, mode='w') as cfile:
        cfile.write(tempfilled)


if __name__ == '__main__':
    main()
import random

def generateRandomMatrix(row, col):
    mat = []
    for r in range(row):
        for c in range(col):
            mat.append(random.randint(0, 31))   # I picked these numbers arbitrarily
    return mat

def main():

    with open('matmul.template', mode='r') as tempfile:
        template = tempfile.read()
    
    rowcount = 4
    colcount = 4
    
    tempfilled = template.format(matsize = rowcount*colcount, mat1=', '.join(map(str, generateRandomMatrix(4,4))), mat2=', '.join(map(str, generateRandomMatrix(4,4))))

    with open('matmul.c', mode='w') as cfile:
        cfile.write(tempfilled)


if __name__ == '__main__':
    main()
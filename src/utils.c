#include "mlp.h"

void free_uint8_matrix(uint8_t **addr, int nrows)
{
    if(!addr)
        return;

    for(int i=0; i<nrows; i++)
        free(addr[i]);
    free(addr);
}

void print_double_matrix(double **addr, int nrows, int ncols)
{
    for(size_t i=0; i<nrows; ++i)
    {
        for(size_t j=0; j<ncols; ++j)
            printf("%.2lf ", addr[i][j]);
        printf("\n");
    }
}

void print_double_vector(double *addr, int nrows)
{
    for(size_t i=0; i<nrows; ++i)
        printf("%.2lf ", addr[i]);
    printf("\n");
}
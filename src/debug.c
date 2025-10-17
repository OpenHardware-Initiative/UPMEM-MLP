#include "mlp.h"

void print_double_matrix(double **addr, int nrows, int ncols)
{
    for(size_t i=0; i<nrows; ++i)
    {
        for(size_t j=0; j<ncols; ++j)
            printf("%lf ", addr[i][j]);
        printf("\n");
    }
}

void print_double_vector(double *addr, int nrows)
{
    for(size_t i=0; i<nrows; ++i)
        printf("%lf ", addr[i]);
    printf("\n");
}
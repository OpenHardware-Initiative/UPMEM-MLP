#include "mlp.h"

void free_layer(LAYER *l)
{
    if(!l)
        return;

    for(int i=0; i<l->num_neurons; ++i) {
        free_neuron(&l->n[i]);
    }
    free(l->n);
    l->n = NULL;

    free(l->inputs);
    free(l->deltas);
    l->inputs = NULL;
    l->deltas = NULL;
    
    l->num_neurons = 0;
}

void free_network(NETWORK *n)
{
    if(!n)
        return;

    for(int i=0; i<n->num_layers; ++i)
        free_layer(&n->l[i]);
    free(n->l);
    n->l = NULL;
    n->num_inputs = 0;
    n->num_layers = 0;
    free(n);
}

void free_neuron(NEURON *n)
{
    if(!n)
        return;
    
    free(n->w);
    free(n->lw);
    free(n->batch_dw);

    n->w = NULL;
    n->lw = NULL;
    n->batch_dw = NULL;
    n->num_weights = 0;
}

void free_float_matrix(float **addr, int nrows)
{
    if(!addr)
        return;
    
    for(int i=0; i<nrows; i++)
        free(addr[i]);
    free(addr);
}

void free_uint8_matrix(uint8_t **addr, int nrows)
{
    if(!addr)
        return;

    for(int i=0; i<nrows; i++)
        free(addr[i]);
    free(addr);
}

void print_float_matrix(float **addr, int nrows, int ncols)
{
    for(size_t i=0; i<nrows; ++i)
    {
        for(size_t j=0; j<ncols; ++j)
            printf("%.2f ", addr[i][j]);
        printf("\n");
    }
}

void print_float_vector(float *addr, int nrows)
{
    for(size_t i=0; i<nrows; ++i)
        printf("%.2f ", addr[i]);
    printf("\n");
}
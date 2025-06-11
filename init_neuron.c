#include "mlp.h"

NEURON *init_neuron(int num_weights)
{
    NEURON *n = (NEURON *) malloc (sizeof(NEURON));
    
    n->num_weights = num_weights;
    n->w    = (double *) malloc (sizeof(double) * n->num_weights);
    n->lw   = (double *) malloc (sizeof(double) * n->num_weights);

    for(int i=0; i<num_weights; i++)
    {
        n->w[i] = (double) rand() / (double) RAND_MAX;
        n->lw[i] = 0;
    }

    return n;
}
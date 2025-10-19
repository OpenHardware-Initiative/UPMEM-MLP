#include "mlp.h"

NEURON *init_neuron(int num_weights)
{
    NEURON *n = (NEURON *) malloc (sizeof(NEURON));
    
    n->num_weights = num_weights;
    n->w    = (double *) malloc (sizeof(double) * n->num_weights);
    n->lw   = (double *) malloc (sizeof(double) * n->num_weights);

    double limit = 1.0/sqrt((double) num_weights);

    for(int i=0; i<num_weights; i++)
    {
        double rand_unit = (double)rand() / (double)RAND_MAX;
        n->w[i] = (rand_unit * 2.0 - 1.0) * limit;
        n->lw[i] = 0;
    }

    return n;
}
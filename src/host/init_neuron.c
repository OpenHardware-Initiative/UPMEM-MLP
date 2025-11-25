#include "mlp.h"

NEURON *init_neuron(int num_weights)
{
    NEURON *n = (NEURON *) malloc (sizeof(NEURON));
    if(!n) {
        return NULL;
    }
    
    n->num_weights = num_weights;

    n->w    = (float *) malloc (sizeof(float) * n->num_weights);
    if(!n->w) {
        free(n);
        return NULL;
    }

    n->lw   = (float *) malloc (sizeof(float) * n->num_weights);
    if(!n->lw) {
        free(n->w);
        free(n);
        return NULL;
    }

    n->batch_dw = (float *) malloc (sizeof(float) * n->num_weights);
    if(!n->batch_dw) {
        free(n->lw);
        free(n->w);
        free(n);
        return NULL;
    }

    float limit = 1.0/sqrt((float) num_weights);

    for(int i=0; i<num_weights; i++)
    {
        float rand_unit = frand();
        n->w[i] = (rand_unit * 2.0 - 1.0) * limit;
        n->lw[i] = n->w[i];
        n->batch_dw[i] = 0;
    }

    return n;
}
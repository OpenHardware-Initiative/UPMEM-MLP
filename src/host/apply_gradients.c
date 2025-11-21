#include "mlp.h"

void apply_gradients(NETWORK *n, int batch_size)
{
    if(batch_size <= 0)
        return;

    for(int i=0; i<n->num_layers; i++)
    {
        LAYER *lp = n->l+i; // ptr to i-th layer of the network n

        for(int j=0; j<lp->num_neurons; j++)
        {
            NEURON *np = lp->n+j;   // ptr to j-th neuron of the i-th layer of the network n

            for(int k=0; k<np->num_weights; k++)    // do the following for all weights "k" of said neuron:
            {
                double previous_weight_update = np->w[k] - np->lw[k];
                double momentum_term = MOMENTUM * previous_weight_update;
                double gradient_term = np->batch_dw[k] / (double) batch_size;

                double old_weight = np->w[k];

                np->lw[k] = old_weight;
                np->w[k] = old_weight + gradient_term + momentum_term;

                np->batch_dw[k] = 0.0;
            }
        }
    }
}
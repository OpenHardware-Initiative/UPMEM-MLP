#include "mlp.h"

LAYER *init_layer(int num_neurons, int num_weights_per_neuron, int batch_size)
{
    LAYER *l = (LAYER *) malloc (sizeof(LAYER));
    if(!l) {
        return NULL;
    }

    l->num_neurons = num_neurons;

    l->inputs = (double*) malloc (batch_size * num_weights_per_neuron * sizeof(double));
    if(!l->inputs) {
        free(l);
        return NULL;
    }

    l->deltas = (double*) malloc (batch_size * num_neurons * sizeof(double));
    if(!l->deltas) {
        free(l->inputs);
        free(l);
        return NULL;
    }

    l->n = (NEURON *) malloc (sizeof(NEURON)*num_neurons);
    if(!l->n) {
        free(l->deltas);
        free(l->inputs);
        free(l);
        return NULL;
    }

    for(int i=0; i<num_neurons; i++)
    {
        NEURON *neuron = l->n+i;
        
        NEURON *temp = init_neuron(num_weights_per_neuron);
        if(!temp) {
            for(int j=0; j<i; ++j) {
                free_neuron(l->n+j);
            }
            free(l->n);
            free(l->deltas);
            free(l->inputs);
            free(l);
            return NULL;
        }
        
        neuron->num_weights = temp->num_weights;
        neuron->w = temp->w;
        neuron->lw = temp->lw;
        neuron->batch_dw = temp->batch_dw;

        free(temp);
    }

    return l;
}
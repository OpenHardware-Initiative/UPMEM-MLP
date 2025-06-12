#include "mlp.h"

LAYER *init_layer(int num_neurons, int num_weights_per_neuron)
{
    LAYER *l = (LAYER *) malloc (sizeof(LAYER));

    l->num_neurons = num_neurons;
    l->n = (NEURON *) malloc (sizeof(NEURON)*num_neurons);

    for(int i=0; i<num_neurons; i++)
    {
        NEURON *neuron = l->n+i;
        
        NEURON *temp = init_neuron(num_weights_per_neuron);
        
        neuron->num_weights = temp->num_weights;
        neuron->w = temp->w;
        neuron->lw = temp->lw;
    }

    return l;
}
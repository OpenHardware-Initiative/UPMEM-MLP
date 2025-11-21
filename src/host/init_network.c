#include "mlp.h"

NETWORK *init_network(int num_inputs, int num_layers, int *num_neurons_per_layer, int batch_size)
{
    NETWORK *n = (NETWORK *) malloc (sizeof(NETWORK));
    if(!n) {
        return NULL;
    }

    n->num_layers = num_layers;
    n->num_inputs = num_inputs;

    n->l = (LAYER *) malloc (sizeof(LAYER)*num_layers);
    if(!n->l) {
        free(n);
        return NULL;
    }

    // initialize i-th layer of the network n
    for(int i=0; i<num_layers; i++) 
    {
        int num_neurons_current_layer = num_neurons_per_layer[i];

        LAYER *current_layer = n->l+i;

        int num_weights_per_neuron;
        if(i == 0)
            num_weights_per_neuron = n->num_inputs + 1;
        else
            num_weights_per_neuron = num_neurons_per_layer[i-1] + 1;

        LAYER *temp = init_layer(num_neurons_current_layer, num_weights_per_neuron, batch_size);
        if(!temp) {
            for(int j=0; j<i; ++j) {
                free_layer(n->l+j);
            }
            free(n->l);
            free(n);
            return NULL;
        }

        current_layer->num_neurons = num_neurons_current_layer;
        current_layer->inputs = temp->inputs;
        current_layer->deltas = temp->deltas;
        current_layer->n = temp->n;

        free(temp);
    }

    return n;
}
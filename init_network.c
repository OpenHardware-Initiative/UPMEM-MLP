#include "init_neuron.c"

NETWORK *init_network(int num_inputs, int num_layers, int *num_neurons_per_layer)
{
    NETWORK *n = (NETWORK *) malloc (sizeof(NETWORK));
    n->num_layers = num_layers;
    n->num_inputs = num_inputs;
    n->l = (LAYER *) malloc (sizeof(LAYER)*num_layers);

    // initialize i-th layer of the network n
    for(int i=0; i<num_layers; i++) 
    {
        int neurons = num_neurons_per_layer[i];

        LAYER *current_layer = n->l+i;

        current_layer->num_neurons = neurons;
        current_layer->n = (NEURON *) malloc (sizeof(NEURON)*neurons);

        // initialize j-th neuron of the i-th layer
        for(int j=0; j<neurons; j++)
        {
            NEURON *neuron = current_layer->n+j;

            int num_weights;
            if(i == 0)
                num_weights = n->num_inputs + 1;
            else
                num_weights = num_neurons_per_layer[i-1] + 1;

            NEURON *temp = init_neuron(num_weights);
            neuron->num_weights = temp->num_weights;
            neuron->w = temp->w;
            neuron->lw = temp->lw;
        }
    }

    return n;
}
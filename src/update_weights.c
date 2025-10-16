#include "mlp.h"

void update_weights(NETWORK *n, int layer_index, double *sample, double* delta, double* previous_y)
{
    LAYER *l = n->l+layer_index;
    int layer_num_neurons = l->num_neurons;

    int is_first_layer = layer_index == 0;

    for(int i=0; i<layer_num_neurons; i++) // for each neuron in the layer n->l[layer_index] do the following:
    {
        NEURON *current_neuron = l->n+i;
        int current_neuron_num_weights = current_neuron->num_weights;

        for(int j=0; j<current_neuron_num_weights; j++) // for each weight of the neuron l->n[i] do the following:
        {
            double previous_weight_update = *(current_neuron->w+j) - *(current_neuron->lw+j);
            double momentum_term = MOMENTUM * previous_weight_update;

            double neuron_input = is_first_layer ? sample[j] : previous_y[j];
            double gradient_term = LEARNING_RATE * delta[i] * neuron_input;

            double old_weight = *(current_neuron->w+j);

            *(current_neuron->lw+j) = old_weight;
            *(current_neuron->w+j) = old_weight + gradient_term + momentum_term;
        }
    }
}
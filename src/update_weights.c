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
            double neuron_input = is_first_layer ? sample[j] : previous_y[j];
            current_neuron->batch_dw[j] += LEARNING_RATE * delta[i] * neuron_input;
        }
    }
}

void apply_batch_gradients(NETWORK *n, int batch_size)
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
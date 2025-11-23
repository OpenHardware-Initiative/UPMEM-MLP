#include "mlp.h"

void accumulate_layer_gradients(LAYER *l, int batch_size, float learning_rate)
{
    if(batch_size <= 0)
        return;

    int num_neurons = l->num_neurons;
    int num_weights = l->n->num_weights;

    float *gradient = (float *) malloc (num_neurons * num_weights * sizeof(float));
    if(!gradient) {
        return;
    }

    float *deltas_T = (float*) malloc (num_neurons * batch_size * sizeof(float));
    if(!deltas_T) {
        free(gradient);
        return;
    }

    transpose_matrix(l->deltas, deltas_T, batch_size, num_neurons);
    multiply_matrix(deltas_T, l->inputs, gradient, num_neurons, batch_size, num_weights);

    for(int n_idx=0; n_idx<num_neurons; n_idx++) {
        NEURON *current_neuron = l->n+n_idx;

        for(int w_idx=0; w_idx<num_weights; w_idx++) {
            current_neuron->batch_dw[w_idx] += learning_rate * gradient[n_idx * num_weights + w_idx];
        }
    }

    free(deltas_T);
    free(gradient);
    return;
}


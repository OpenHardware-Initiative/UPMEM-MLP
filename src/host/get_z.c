#include "mlp.h"

// samples -> get_z -> preactivation

float *get_z(NETWORK *n, int layer_index, float *sample)
{
    LAYER *current_layer = n->l+layer_index;
    int z_neuroncount = current_layer->num_neurons;
    int z_weightcount = current_layer->n->num_weights;
    int is_first_layer = layer_index == 0;

    float *z = (float *) malloc (sizeof(float)* z_neuroncount);
    if(!z) {
        fprintf(stderr, "Error 10005\n");
        return NULL;
    }

    float *z_prev = is_first_layer ? sample : get_y(n, layer_index-1, sample);

    for(size_t i=0; i<z_neuroncount; ++i) {
        z[i] = 0;
        NEURON *current_neuron = current_layer->n+i;
        for(size_t j=0; j<z_weightcount; ++j) {
            z[i] += current_neuron->w[j] * z_prev[j];
        }
    }

    if(!is_first_layer)
        free(z_prev);

    return z;
}
#include "mlp.h"

double *get_z(NETWORK *n, int layer_index, double *sample)
{
    LAYER *current_layer = n->l+layer_index;
    int z_neuroncount = current_layer->num_neurons;
    int z_weightcount = current_layer->n->num_weights;

    double *z = (double *) malloc (sizeof(double)* z_neuroncount);

    double *z_prev = layer_index==0 ? sample : get_y(n, layer_index-1, sample);

    for(size_t i=0; i<z_neuroncount; ++i) {
        z[i] = 0;
        NEURON *current_neuron = current_layer->n+i;
        for(size_t j=0; j<z_weightcount; ++j) {
            z[i] += current_neuron->w[j] * z_prev[j];
        }
    }

    return z;
}
#include "mlp.h"

// preactivation -> get_y -> activation

float *get_y(NETWORK *n, int layer_index, float *sample)
{
    LAYER *current_layer = n->l+layer_index;
    int is_current_layer_last_layer = (n->num_layers == layer_index + 1);
    int y_size = current_layer->num_neurons;

    if(!is_current_layer_last_layer) // add bias node
        y_size++;

    float *z = get_z(n, layer_index, sample);

    float *y = (float *) malloc (sizeof(float)*y_size);
    if(!y) {
        fprintf(stderr, "Error 10006\n");
        return NULL;
    }

    for(size_t i=0; i<y_size; ++i) {
        if(is_current_layer_last_layer)
            y[i] = get_activation(z[i]);
        else
            y[i] = i==0 ? 1 : get_activation(z[i-1]);
    }

    free(z);

    return y;
}
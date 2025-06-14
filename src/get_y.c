#include "mlp.h"

double *get_y(NETWORK *n, int layer_index, double *sample)
{
    LAYER *current_layer = n->l+layer_index;
    int is_current_layer_last_layer = (n->num_layers == layer_index + 1);
    int y_size = current_layer->num_neurons;

    if(!is_current_layer_last_layer) // add bias node
        y_size++;

    double *z = get_z(n, layer_index, sample);
    double *y = (double *) malloc (sizeof(double)*y_size);

    for(size_t i=0; i<y_size; ++i) {
        if(is_current_layer_last_layer)
            y[i] = activation(z[i]);
        else
            y[i] = i==0 ? 1 : activation(z[i-1]);
    }

    return y;
}
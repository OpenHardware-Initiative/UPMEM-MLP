#include "mlp.h"

float *get_delta(NETWORK *n, float* sample, float* ideal, int layer_index)
{
    int layer_size = (n->l+layer_index)->num_neurons;

    float *d = (float*) malloc (sizeof(float) * layer_size);
    if(!d) {
        fprintf(stderr, "Error 10010\n");
        return NULL;
    }

    float *z = get_z(n, layer_index, sample);
    if(!z) {
        fprintf(stderr, "Error 10011\n");
        free(d);
        return NULL;
    }

    int is_current_layer_last_layer = (n->num_layers == layer_index + 1);

    if(is_current_layer_last_layer)
    {
        float *y = get_y(n, layer_index, sample);
        if(!y) {
            fprintf(stderr, "Error 10012\n");
            free(d);
            free(z);
            return NULL;
        }

        for(int i=0; i<layer_size; i++)
            d[i] = (ideal[i] - y[i]) * get_activation_derivative(z[i]);

        free(y);
    }
    else
    {
        float *next_d = get_delta(n, sample, ideal, layer_index+1);
        if(!next_d) {
            fprintf(stderr, "Error 10013\n");
            free(d);
            free(z);
            return NULL;
        }

        LAYER *next_layer = n->l+layer_index+1;

        for(int j=0; j<layer_size; j++)
        {
            d[j] = 0.0;

            for(int k=0; k<next_layer->num_neurons; k++)
            {
                NEURON *neuron_next = next_layer->n+k;
                d[j] += *(neuron_next->w+j+1) * next_d[k];      // the +1 is for the bias
            }

            d[j] *= get_activation_derivative(z[j]);
        }

        free(next_d);
    }

    free(z);

    return d;
}
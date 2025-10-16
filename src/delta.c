#include "mlp.h"

double *delta(NETWORK *n, double* sample, double* ideal, int layer_index)
{
    int layer_size = (n->l+layer_index)->num_neurons;
    double *d = (double*) malloc (sizeof(double) * layer_size);
    double *z = get_z(n, layer_index, sample);

    int is_current_layer_last_layer = (n->num_layers == layer_index + 1);

    if(is_current_layer_last_layer)
    {
        double *y = get_y(n, layer_index, sample);

        for(int i=0; i<layer_size; i++)
            d[i] = (ideal[i] - sample[i]) * activation_derivative(z[i]);
        
    }
    else
    {
        double *next_d = delta(n, sample, ideal, layer_index+1);
        LAYER *next_layer = n->l+layer_index+1;

        for(int j=0; j<layer_size; j++)
        {
            d[j] = 0.0;

            for(int k=0; k<next_layer->num_neurons; k++)
            {
                NEURON *neuron_next = next_layer->n+k;
                d[j] += *(neuron_next->w+j+1) * next_d[k];      // the +1 is for bias node
            }

            d[j] *= activation_derivative(z[j]);
        }
    }

    return d;
}
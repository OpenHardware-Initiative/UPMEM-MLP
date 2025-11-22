#include "mlp.h"

float *get_total_loss(NETWORK *n, float **samples, float **ideal, int nsamples)
{
    float *total_loss = (float*) malloc (sizeof(float));
    if(!total_loss) {
        fprintf(stderr, "Error 10007\n");
        return NULL;
    }

    *total_loss = 0.0;

    LAYER *last_layer = n->l+(n->num_layers-1);

    for(int i=0; i<nsamples; ++i) {
        float *y = get_y(n, n->num_layers-1, samples[i]);
        if(!y) {
            fprintf(stderr, "Error 10008\n");
            free(total_loss);
            return NULL;
        }
        *total_loss += sse(y, ideal[i], last_layer->num_neurons) / (float)nsamples;
        free(y);
    }

    return total_loss;
}
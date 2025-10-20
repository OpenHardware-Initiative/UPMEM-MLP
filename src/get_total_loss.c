#include "mlp.h"

double *get_total_loss(NETWORK *n, double **samples, double **ideal, int nsamples)
{
    double *total_loss = (double*) malloc (sizeof(double));
    if(!total_loss) {
        fprintf(stderr, "Error 10007\n");
        return NULL;
    }

    LAYER *last_layer = n->l+(n->num_layers-1);

    for(int i=0; i<nsamples; ++i) {
        double *y = get_y(n, n->num_layers-1, samples[i]);
        if(!y) {
            fprintf(stderr, "Error 10008\n");
            free(total_loss);
            return NULL;
        }
        *total_loss += sse(y, ideal[i], last_layer->num_neurons) / (double)nsamples;
        free(y);
    }

    return total_loss;
}
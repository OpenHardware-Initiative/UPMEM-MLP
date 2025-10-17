#include "mlp.h"
#include "mnist.h"

unsigned int rseed = 42;

int main()
{
    srand(rseed);

    int rows;

    int num_inputs = NUM_FEATURES;
    int num_layers = 5;
    int num_neurons_per_layer[] = {NUM_FEATURES, 1000, 1000, 100, NUM_LABELS};

    NETWORK *n = init_network(num_inputs, num_layers, num_neurons_per_layer);

    double **samples    = (double **) malloc (sizeof(double*)*NUM_TRAIN_SAMPLES);
    double *labels      = (double *)  malloc (sizeof(double) *NUM_TRAIN_SAMPLES);

    uint8_t **sample_data   = read_image_data(TRAINING_IMAGES_FILE, &rows, NUM_FEATURES);
    uint8_t **label_data    = read_image_data(TRAINING_LABELS_FILE, &rows, 1);

    // save data into `samples` and `labels`
    for(size_t i=0; i<NUM_TRAIN_SAMPLES; ++i) {
        *(samples+i)    = (double *) malloc (sizeof(double)*NUM_FEATURES);
        
        samples[i][0] = -1.0;   // bias
        for(size_t j=1; j<(NUM_FEATURES+1); ++j) {
            samples[i][j] = sample_data[i][j];
        }
        
        labels[i] = label_data[i][0];
    }

    // print samples to check if all saved correctly
    for(size_t i=0; i<5; ++i) {
        for(size_t j=0; j<(NUM_FEATURES+1); ++j) {
            printf("%lf ", samples[i][j]);
        }
        printf("\n");
    }

    return 0;
}
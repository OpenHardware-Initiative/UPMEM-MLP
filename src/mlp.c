#include "mlp.h"
#include "mnist.h"

unsigned int rseed = 42;

int main()
{
    srand(rseed);

    int sample_rows, label_rows;
    int epoch = 0;

    int num_inputs = NUM_FEATURES;
    int num_layers = 5;
    int num_neurons_per_layer[] = {NUM_FEATURES, 1000, 1000, 100, NUM_LABELS};

    NETWORK *n = init_network(num_inputs, num_layers, num_neurons_per_layer);
    if(!n) {
        fprintf(stderr, "Error 10004\n");
        return 1;
    }

    double **samples    = (double **) malloc (sizeof(double*)*NUM_TRAIN_SAMPLES);
    double **labels     = (double **) malloc (sizeof(double*)*NUM_TRAIN_SAMPLES);

    uint8_t **sample_data   = read_image_data(TRAINING_IMAGES_FILE, &sample_rows, NUM_FEATURES);
    uint8_t **label_data    = read_image_data(TRAINING_LABELS_FILE, &label_rows, 1);

    // save data into `samples` and `labels`
    for(size_t i=0; i<NUM_TRAIN_SAMPLES; ++i) {
        *(samples+i)    = (double *) malloc (sizeof(double)*(NUM_FEATURES+1));
        *(labels+i)     = (double *) malloc (sizeof(double)*NUM_LABELS);
        
        samples[i][0] = -1.0;   // bias
        for(size_t j=1; j<(NUM_FEATURES+1); ++j) {
            samples[i][j] = sample_data[i][j-1] / 255.0;
        }
        
        for(size_t j=0; j<NUM_LABELS; ++j) {
            labels[i][j] = label_data[i][0] == j;
        }
    }

    free_uint8_matrix(sample_data, sample_rows);
    free_uint8_matrix(label_data, label_rows);

#ifdef DEBUG
    printf("PROGRAM RUN IN DEBUG MODE\n\n");

    // print samples & labels to check if all is saved correctly into program memory
    printf("Samples:\n");
    print_double_matrix(samples, 2, NUM_FEATURES+1);

    printf("Labels:\n");
    print_double_matrix(labels, 5, NUM_LABELS);

    printf("Starting training...\n");
#endif

    LAYER* last_layer = n->l+(n->num_layers-1);

    while(1) {

        double loss_delta = 0.0;
        double loss_prev = 0.0;
        double loss_new = 0.0;

        for(int i=0; i<NUM_TRAIN_SAMPLES; ++i) {
            double *Y = get_y(n, n->num_layers-1, samples[i]);
            loss_prev += sse(Y, labels[i], last_layer->num_neurons) / (double)NUM_TRAIN_SAMPLES;
        }

        for(int i=0; i<NUM_TRAIN_SAMPLES; ++i) {
            for(int j=n->num_layers-1; j>=0; --j) {
                double *d = delta(n, samples[i], labels[i], j);
                double *py = j ? get_y(n, j-1, samples[i]) : NULL;
                update_weights(n, j, samples[i], d, py);
            }
        }

        for(int i=0; i<NUM_TRAIN_SAMPLES; ++i) {
            double *Y = get_y(n, n->num_layers-1, samples[i]);
            loss_new += sse(Y, labels[i], last_layer->num_neurons) / (double)NUM_TRAIN_SAMPLES;
        }

        loss_delta = fabs(loss_new - loss_prev);

        epoch++;
        
#ifdef DEBUG
        printf("Epoch %d --- loss_delta = %.12lf\n", epoch, loss_delta);
#endif

        if(loss_delta < EPSILON)
            break;
    }

    printf("Training complete in %d epochs\n", epoch);

    free_network(n);

    return 0;
}
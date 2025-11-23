#include "mlp.h"
#include "mnist.h"
#include "upmem.h"
#include <x86intrin.h>

unsigned int rseed = 42;

int main()
{
    srand(rseed);

    int sample_rows, label_rows;
    int epoch = 0;

    int num_inputs = NUM_FEATURES;
    int num_layers = 3;
    int num_neurons_per_layer[] = {NUM_FEATURES, 10, NUM_LABELS};

    NETWORK *n = init_network(num_inputs, num_layers, num_neurons_per_layer, BATCH_SIZE);
    if(!n) {
        fprintf(stderr, "Error 10004\n");
        return 1;
    }

    float **samples    = (float **) malloc (sizeof(float*)*NUM_TRAIN_SAMPLES);
    float **labels     = (float **) malloc (sizeof(float*)*NUM_TRAIN_SAMPLES);

    uint8_t **sample_data   = read_image_data(TRAINING_SAMPLES_FILE, &sample_rows, NUM_FEATURES);
    uint8_t **label_data    = read_image_data(TRAINING_LABELS_FILE, &label_rows, 1);

    // save data into `samples` and `labels`
    for(size_t i=0; i<NUM_TRAIN_SAMPLES; ++i) {
        *(samples+i)    = (float *) malloc (sizeof(float)*(NUM_FEATURES+1));
        *(labels+i)     = (float *) malloc (sizeof(float)*NUM_LABELS);
        
        samples[i][0] = 0.0;   // bias
        for(size_t j=1; j<(NUM_FEATURES+1); ++j) {
            samples[i][j] = (sample_data[i][j-1] / 127.5) - 1.0;
        }
        
        for(size_t j=0; j<NUM_LABELS; ++j) {
            labels[i][j] = label_data[i][0] == j;
        }
    }

    free_uint8_matrix(sample_data, sample_rows);
    free_uint8_matrix(label_data, label_rows);

#ifdef DEBUG
    // print samples & labels to check if all is saved correctly into program memory
    printf("===== Samples =====\n\n");
    print_float_matrix(samples, 2, NUM_FEATURES+1);
    printf("\n");

    printf("===== Labels =====\n\n");
    print_float_matrix(labels, 5, NUM_LABELS);
    printf("\n");

    printf("Starting training...\n\n");
#endif

    int num_batches = (NUM_TRAIN_SAMPLES + BATCH_SIZE - 1) / BATCH_SIZE;

#ifdef EVAL
    unsigned long long cc_start = __rdtsc();
#endif

    while(1) {

        float learning_rate_epoch = LEARNING_RATE * powf(DECAY_RATE, epoch);

        float *loss_prev = get_total_loss(n, samples, labels, NUM_TRAIN_SAMPLES);
        if(!loss_prev) {
            fprintf(stderr, "Error 10014\n");
            return 1;
        }

        for(int b=0; b<num_batches; ++b) {
            int batch_start = b * BATCH_SIZE;
            int batch_end = batch_start + BATCH_SIZE;
            
            if(batch_end > NUM_TRAIN_SAMPLES)
                batch_end = NUM_TRAIN_SAMPLES;

            int actual_batch_size = batch_end - batch_start;

            for(int i=batch_start, batch_ctr = 0; i<batch_end; ++i, batch_ctr++) {
                for(int j=n->num_layers-1; j>=0; --j) {
                    LAYER *lp = n->l+j;     // ptr to layer j of network n

                    float *d = get_delta(n, samples[i], labels[i], j);

                    memcpy(lp->deltas+batch_ctr*lp->num_neurons, d, lp->num_neurons * sizeof(float));

                    float *py = j ? get_y(n, j-1, samples[i]) : NULL;
                    if(j && !py) {
                        fprintf(stderr, "Error 10009\n");
                        return 1;
                    }

                    memcpy(lp->inputs+batch_ctr*lp->n->num_weights, (j ? py : samples[i]), lp->n->num_weights * sizeof(float));

                    free(d);
                    if(j) free(py);
                }
            }

            for(int l_idx=0; l_idx<n->num_layers; l_idx++)
                accumulate_layer_gradients(n->l+l_idx, actual_batch_size, learning_rate_epoch);

            apply_gradients(n, actual_batch_size);
        }

        float *loss_new = get_total_loss(n, samples, labels, NUM_TRAIN_SAMPLES);
        if(!loss_new) {
            fprintf(stderr, "Error 10015\n");
            return 1;
        }

        float loss_delta = fabs(*loss_new - *loss_prev);

        epoch++;
        
#ifdef VERBOSE
        printf("Epoch %-3d --- Lost Delta = %.9f --- Final Loss = %.6f\n", epoch, loss_delta, *loss_new);
#endif

        free(loss_prev);
        free(loss_new);

        if(loss_delta < EPSILON || epoch == MAX_EPOCH)
            break;
    }

#ifdef EVAL
    unsigned long long cc_end = __rdtsc();
    printf("Training complete | %lld cycles | %d epochs\n", cc_end-cc_start, epoch);
#endif

#ifdef DEBUG
    printf("\n===== Weights =====\n\n");
    for(int i=0; i<num_layers; i++) {
        LAYER *lp = n->l+i;             // ptr to i-th layer of the network n
        for(int j=0; j<lp->num_neurons; j++) {
            NEURON *np = lp->n+j;       // ptr to j-th neuron of the i-th layer of network n
            print_float_vector(np->w, np->num_weights);
            printf("\n");
        }
        printf("\n\n");
    }
#endif

    // free DPUs if UPMEM was deployed
    if(upmem_initialized) {
        free_dpus();
    }

    // memory cleanup before termination
    free_float_matrix(samples, NUM_TRAIN_SAMPLES);
    free_float_matrix(labels, NUM_TRAIN_SAMPLES);
    free_network(n);

    return 0;
}
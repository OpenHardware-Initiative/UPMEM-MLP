#include "mlp.h"
#include "test.h"

int test_accumulate_layer_gradients()
{
    int test_pass_fail = 1;

    int num_neurons_per_layers[] = {4, 4};

    NETWORK *n = init_network(4, 2, num_neurons_per_layers, BATCH_SIZE);

    LAYER *first_layer = n->l;

    // inputs is 1x5 matrix
    for(int i=0; i<1*5; i++)
        first_layer->inputs[i] = ((float) rand() / (float) RAND_MAX) * 20;

    // deltas is a 1x4 identity matrix
    for(int i=0; i<1*4; i++)
        first_layer->deltas[i] = 1.0;

    float batch_dw_ideal[4][5] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for(int i=0; i<4; i++)
        for(int j=0; j<5; j++)
            batch_dw_ideal[i][j] += LEARNING_RATE * first_layer->inputs[j];

    accumulate_layer_gradients(n->l+0, 1, LEARNING_RATE);

    for(int i=0; i<4; i++)
        for(int j=0; j<5; j++)
            test_pass_fail &= batch_dw_ideal[i][j] == first_layer->n[i].batch_dw[j];

    return test_pass_fail;
}

int main()
{
    int test_pass_fail = test_accumulate_layer_gradients();

    TEST_PASS_FAIL(test_pass_fail);
}
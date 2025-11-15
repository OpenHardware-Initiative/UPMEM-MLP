#include "mlp.h"
#include "test.h"

int test_accumulate_gradients()
{
    int test_pass_fail = 1;

    int num_neurons_per_layers[] = {3, 3};
    double samples[] = {1, 1, 1, 1};
    double delta[] = {1, 1, 1, 1};

    NETWORK *n = init_network(3, 2, num_neurons_per_layers);

    n->l[0].n[0].lw[0] = 0.0;
    n->l[0].n[0].lw[1] = 0.0;
    n->l[0].n[0].lw[2] = 0.0;
    n->l[0].n[0].lw[3] = 0.0;

    n->l[0].n[1].lw[0] = 0.0;
    n->l[0].n[1].lw[1] = 0.0;
    n->l[0].n[1].lw[2] = 0.0;
    n->l[0].n[1].lw[3] = 0.0;

    n->l[0].n[2].lw[0] = 0.0;
    n->l[0].n[2].lw[1] = 0.0;
    n->l[0].n[2].lw[2] = 0.0;
    n->l[0].n[2].lw[3] = 0.0;

    n->l[0].n[0].w[0] = 1.0;
    n->l[0].n[0].w[1] = 1.0;
    n->l[0].n[0].w[2] = 1.0;
    n->l[0].n[0].w[3] = 1.0;

    n->l[0].n[1].w[0] = 1.0;
    n->l[0].n[1].w[1] = 1.0;
    n->l[0].n[1].w[2] = 1.0;
    n->l[0].n[1].w[3] = 1.0;

    n->l[0].n[2].w[0] = 1.0;
    n->l[0].n[2].w[1] = 1.0;
    n->l[0].n[2].w[2] = 1.0;
    n->l[0].n[2].w[3] = 1.0;

    accumulate_gradients(n, 0, samples, delta, samples);

    for(int i=0; i<4; i++)
        test_pass_fail &= (n->l[0].n[0].lw[i] == 0.0) && (n->l[0].n[0].w[i] == 1.0) && (n->l[0].n[0].batch_dw[i] == LEARNING_RATE);

    return test_pass_fail;
}

int main()
{
    int test_pass_fail = test_accumulate_gradients();

    TEST_PASS_FAIL(test_pass_fail);
}
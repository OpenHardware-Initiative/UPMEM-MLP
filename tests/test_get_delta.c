#include "mlp.h"
#include "test.h"

int test_get_delta()
{
    int test_pass_fail = 1;

    int num_neurons_per_layers[] = {3, 3};
    float samples[] = {1, 1, 1, 1};
    float ideals[] = {3, 3, 3, 3};

    NETWORK *n = init_network(3, 2, num_neurons_per_layers, BATCH_SIZE);

    n->l[1].n[0].w[0] = 1.0;
    n->l[1].n[0].w[1] = 1.0;
    n->l[1].n[0].w[2] = 1.0;
    n->l[1].n[0].w[3] = 1.0;

    n->l[1].n[1].w[0] = 1.0;
    n->l[1].n[1].w[1] = 1.0;
    n->l[1].n[1].w[2] = 1.0;
    n->l[1].n[1].w[3] = 1.0;

    n->l[1].n[2].w[0] = 1.0;
    n->l[1].n[2].w[1] = 1.0;
    n->l[1].n[2].w[2] = 1.0;
    n->l[1].n[2].w[3] = 1.0;

    // test last layer delta

    float *d_last_layer = get_delta(n, samples, ideals, 1);

    for(int i=0; i<3; i++)
    {
        test_pass_fail &= TEST_FLOAT_EQ(d_last_layer[i],
                                        (ideals[i] - get_y(n, 1, samples)[i]) * get_activation_derivative(get_z(n, 1, samples)[i]),
                                        EPS_TEST);
    }

    // test before-last layer delta

    float *d_first_layer = get_delta(n, samples, ideals, 0);

    for(int i=0; i<3; i++)
    {
        test_pass_fail &= TEST_FLOAT_EQ(d_first_layer[i],
                                        (d_last_layer[0] + d_last_layer[1] + d_last_layer[2]) * get_activation_derivative(get_z(n, 0, samples)[i]),
                                        EPS_TEST);
    }

    return test_pass_fail;
}

int main()
{
    int test_pass_fail = test_get_delta();

    TEST_PASS_FAIL(test_pass_fail);
}
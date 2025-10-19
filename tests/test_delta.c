#include "mlp.h"
#include "test.h"

int test_delta()
{
    int test_pass_fail = 1;

    int num_neurons_per_layers[] = {3, 3};
    double samples[] = {1, 1, 1, 1};
    double ideals[] = {3, 3, 3, 3};

    NETWORK *n = init_network(3, 2, num_neurons_per_layers);

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

    double *d_last_layer = delta(n, samples, ideals, 1);

    for(int i=0; i<3; i++)
    {
        test_pass_fail &= (d_last_layer[i] == (ideals[i] - get_y(n, 1, samples)[i]) * activation_derivative(get_z(n, 1, samples)[i]));
    }

    // test before-last layer delta

    double *d_first_layer = delta(n, samples, ideals, 0);

    for(int i=0; i<3; i++)
    {
        test_pass_fail &= (d_first_layer[i] == (d_last_layer[0] + d_last_layer[1] + d_last_layer[2]) * activation_derivative(get_z(n, 0, samples)[i]));
    }

    return test_pass_fail;
}

int main()
{
    int test_pass_fail = test_delta();

    TEST_PASS_FAIL(test_pass_fail);
}
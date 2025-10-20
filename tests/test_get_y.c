#include "mlp.h"
#include "test.h"

int test_get_y()
{
    int num_neurons_per_layers[] = {3, 3};
    double samples[] = {1, 1, 1, 1};

    NETWORK *n = init_network(3, 2, num_neurons_per_layers);

    n->l[0].n[0].w[0] = -1.0;
    n->l[0].n[0].w[1] = 1.0;
    n->l[0].n[0].w[2] = 1.0;
    n->l[0].n[0].w[3] = 1.0;

    n->l[0].n[1].w[0] = -1.0;
    n->l[0].n[1].w[1] = 5.0;
    n->l[0].n[1].w[2] = 1.0;
    n->l[0].n[1].w[3] = 1.0;

    n->l[0].n[2].w[0] = -1.0;
    n->l[0].n[2].w[1] = 0.0;
    n->l[0].n[2].w[2] = 0.0;
    n->l[0].n[2].w[3] = 0.0;

    double *y = get_y(n, 0, samples);
    double *z = get_z(n, 0, samples);

    // printf("y[0] == %.2lf\n", y[0]);
    // printf("y[1] == %.2lf\n", y[1]);
    // printf("y[2] == %.2lf\n", y[2]);

    int test_pass_fail = (y[0] == 1)
                        && (y[1] == get_activation(z[0]))
                        && (y[2] == get_activation(z[1]));

    y = get_y(n, 1, samples);
    z = get_z(n, 1, samples);

    test_pass_fail = test_pass_fail
                    && (y[0] == get_activation(z[0]))
                    && (y[1] == get_activation(z[1]))
                    && (y[2] == get_activation(z[2]));

    return test_pass_fail;
}

int main()
{
    int test_pass_fail = test_get_y();
    
    TEST_PASS_FAIL(test_pass_fail)
}
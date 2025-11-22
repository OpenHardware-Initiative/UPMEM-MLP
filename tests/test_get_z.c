#include "mlp.h"
#include "test.h"

int test_get_z()
{
    int num_neurons_per_layers[] = {3, 3};
    float samples[] = {1, 1, 1, 1};

    NETWORK *n = init_network(3, 2, num_neurons_per_layers, BATCH_SIZE);
    
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

    float *z = get_z(n, 0, samples);

    // printf("z[0] == %.2f\n", z[0]);
    // printf("z[1] == %.2f\n", z[1]);
    // printf("z[2] == %.2f\n", z[2]);

    int test_pass_fail = (z[0] == 2) && (z[1] == 6) && (z[2] == -1);

    return test_pass_fail;
}

int main()
{
    int test_pass_fail = test_get_z();
    
    TEST_PASS_FAIL(test_pass_fail)
}
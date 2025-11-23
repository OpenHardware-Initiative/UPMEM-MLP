#include "mlp.h"
#include "test.h"

int test_drand()
{
    int test_pass_fail = 1;

    for(int i=0; i<10; i++)
    {
        float test_value = drand();

        test_pass_fail &= (test_value >= 0.0) && (test_value <= 1.0);
    }

    return test_pass_fail;
}

int main()
{
    int test_pass_fail = test_drand();

    TEST_PASS_FAIL(test_pass_fail)
}
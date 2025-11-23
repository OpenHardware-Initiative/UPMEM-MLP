#include "mlp.h"
#include "test.h"

int test_sse()
{
    float real[]   = {3, 4, 4, 4};
    float ideal[]  = {4, 4, 4, 4};
    int test_pass_fail = 1;

    float sse_result = sse(real, ideal, 4);

    test_pass_fail &= TEST_FLOAT_EQ(sse_result, 1, EPS_TEST);

    real[0] = 4;
    sse_result = sse(real, ideal, 4);
    test_pass_fail &= TEST_FLOAT_EQ(sse_result, 0, EPS_TEST);

    real[0] = 6;
    sse_result = sse(real, ideal, 4);
    test_pass_fail &= TEST_FLOAT_EQ(sse_result, 4, EPS_TEST);

    real[0] = 6;
    real[1] = 2;
    sse_result = sse(real, ideal, 4);
    test_pass_fail &= TEST_FLOAT_EQ(sse_result, 8, EPS_TEST);

    return test_pass_fail;
}

int main()
{
    int test_result = test_sse();

    TEST_PASS_FAIL(test_result)
}
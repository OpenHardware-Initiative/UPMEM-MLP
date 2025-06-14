#include "mlp.h"
#include "test.h"

int test_sse()
{
    double real[]   = {3, 4, 4, 4};
    double ideal[]  = {4, 4, 4, 4};
    int test_pass_fail = 1;

    double sse_result = sse(real, ideal, 4);

    test_pass_fail = test_pass_fail && (sse_result == 1);

    real[0] = 4;
    sse_result = sse(real, ideal, 4);
    test_pass_fail = test_pass_fail && (sse_result == 0);

    real[0] = 6;
    sse_result = sse(real, ideal, 4);
    test_pass_fail = test_pass_fail && (sse_result == 4);

    real[0] = 6;
    real[1] = 2;
    sse_result = sse(real, ideal, 4);
    test_pass_fail = test_pass_fail && (sse_result == 8);

    return test_pass_fail;
}

int main()
{
    int test_result = test_sse();

    TEST_PASS_FAIL(test_result)
}
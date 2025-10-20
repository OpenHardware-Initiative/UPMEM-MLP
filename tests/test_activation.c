#include "mlp.h"
#include "test.h"

int test_activation(double x)
{
    double activation_result = get_activation(x);
    double activation_derivative_result = get_activation_derivative(x);

    double expected_activation_derivative = 1 - pow(activation_result, 2);

    if(abs(activation_derivative_result - expected_activation_derivative) < 1e-5)
        return 1;
    
    return 0;
}

int main()
{
    int test_pass_fail = test_activation(0.5)
                        && test_activation(0.1)
                        && test_activation(0.9)
                        && test_activation(0)
                        && test_activation(1);

    TEST_PASS_FAIL(test_pass_fail)
}
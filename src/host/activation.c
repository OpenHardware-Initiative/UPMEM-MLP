#include "mlp.h"

float get_activation(float x)
{
    return tanhf(x);
}

float get_activation_derivative(float x)
{
    return 1.0 / powf(coshf(x), 2);
}
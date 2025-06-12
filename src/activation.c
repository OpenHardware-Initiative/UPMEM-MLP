#include "mlp.h"

double activation(double x)
{
    return tanh(x);
}

double activation_derivative(double x)
{
    return 1.0 / pow(cosh(x), 2);
}
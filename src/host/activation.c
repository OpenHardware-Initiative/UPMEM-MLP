#include "mlp.h"

double get_activation(double x)
{
    return tanh(x);
}

double get_activation_derivative(double x)
{
    return 1.0 / pow(cosh(x), 2);
}
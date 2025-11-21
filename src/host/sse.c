#include "mlp.h"

double sse(double *real, double *ideal, int length)
{
    double sse = 0.0;   // Sum of squared errors

    for(size_t i=0; i<length; ++i) {
        double raw_error = ideal[i]-real[i];
        sse += pow(raw_error, 2);
    }

    return sse;
}
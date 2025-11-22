#include "mlp.h"

float sse(float *real, float *ideal, int length)
{
    float sse = 0.0;   // Sum of squared errors

    for(size_t i=0; i<length; ++i) {
        float raw_error = ideal[i]-real[i];
        sse += powf(raw_error, 2);
    }

    return sse;
}
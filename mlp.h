#ifndef MLP_H
#define MLP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define RATE 0.1
#define EPSILON 0.0000005
#define MOMENTUM 0.8

typedef struct {
    int num_weights;
    double *w, *lw;
} NEURON;

typedef struct {
    int size;
    NEURON *n;
} LAYER;

typedef struct {
    int inputs, layers;
    LAYER *l;
} NETWORK;

#endif
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
    int num_neurons;
    NEURON *n;
} LAYER;

typedef struct {
    int num_inputs, num_layers;
    LAYER *l;
} NETWORK;

NEURON *init_neuron(int);
NETWORK *init_network(int, int, int*);
uint8_t **read_image_data(const char*, int*, int);

#endif
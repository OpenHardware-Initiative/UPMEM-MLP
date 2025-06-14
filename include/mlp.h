#ifndef MLP_H
#define MLP_H

#include <math.h>
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

double activation(double x);
double activation_derivative(double x);
NEURON *init_neuron(int num_weights);
LAYER *init_layer(int num_neurons, int num_weights_per_neuron);
NETWORK *init_network(int num_inputs, int num_layers, int *num_inputs_per_layer);
double *get_y(NETWORK *n, int layer_index, double *sample);
double *get_z(NETWORK *n, int layer_index, double *sample);
uint8_t **read_image_data(const char *filename, int *num_rows, const int num_cols);
double sse(double *real, double *ideal, int length);

#endif
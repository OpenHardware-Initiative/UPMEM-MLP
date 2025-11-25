#ifndef MLP_H
#define MLP_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BATCH_SIZE
#define BATCH_SIZE 1
#endif

#ifndef DECAY_RATE
#define DECAY_RATE 0.95
#endif

#ifndef EPSILON
#define EPSILON 0.0000005
#endif

#ifndef LEARNING_RATE
#define LEARNING_RATE 0.01
#endif

#ifndef MAX_EPOCH
#define MAX_EPOCH 30
#endif

#ifndef MOMENTUM
#define MOMENTUM 0.8
#endif

extern unsigned int rseed;

typedef struct {
    int num_weights;
    float *w, *lw;
    float *batch_dw;
} NEURON;

typedef struct {
    int num_neurons;
    float *inputs, *deltas;
    NEURON *n;
} LAYER;

typedef struct {
    int num_inputs, num_layers;
    LAYER *l;
} NETWORK;

void accumulate_layer_gradients(LAYER *l, int batch_size, float learning_rate);
void apply_gradients(NETWORK *n, int batch_size);
float frand();
float get_activation(float x);
float get_activation_derivative(float x);
float *get_delta(NETWORK *n, float *samples, float *ideal, int layer_index);
float *get_total_loss(NETWORK *n, float **samples, float **ideal, int nsamples);
float *get_y(NETWORK *n, int layer_index, float *sample);
float *get_z(NETWORK *n, int layer_index, float *sample);
LAYER *init_layer(int num_neurons, int num_weights_per_neuron, int batch_size);
NETWORK *init_network(int num_inputs, int num_layers, int *num_inputs_per_layer, int batch_size);
NEURON *init_neuron(int num_weights);
void multiply_matrix(const float *A, const float *B, float *C, int rows_a, int cols_a, int cols_b);
void multiply_matrix_naive(const float *A, const float *B, float *C, int rows_a, int cols_a, int cols_b);
uint8_t **read_image_data(const char *filename, int *num_rows, const int num_cols);
float sse(float *real, float *ideal, int length);
void transpose_matrix(const float *A, float *C, int rows, int cols);

//
// utility functions
//

void free_layer(LAYER *l);
void free_network(NETWORK *n);
void free_neuron(NEURON *n);

void free_float_matrix(float **addr, int nrows);
void free_uint8_matrix(uint8_t **addr, int nrows);

void print_float_matrix(float **addr, int nrows, int ncols);
void print_float_vector(float *addr, int nrows);

#endif

#ifndef MLP_H
#define MLP_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LEARNING_RATE 0.1

#ifndef BATCH_SIZE
#define BATCH_SIZE 1
#endif

#ifndef EPSILON
#define EPSILON 0.0000005
#endif

#define MOMENTUM 0.8

#ifndef MAX_EPOCH
#define MAX_EPOCH 30
#endif

extern unsigned int rseed;

typedef struct {
    int num_weights;
    double *w, *lw;
    double *batch_dw;
} NEURON;

typedef struct {
    int num_neurons;
    double *inputs, *deltas;
    NEURON *n;
} LAYER;

typedef struct {
    int num_inputs, num_layers;
    LAYER *l;
} NETWORK;

double get_activation(double x);
double get_activation_derivative(double x);
double *get_delta(NETWORK *N, double* samples, double* ideal, int layer_index);
double drand();
NEURON *init_neuron(int num_weights);
LAYER *init_layer(int num_neurons, int num_weights_per_neuron, int batch_size);
NETWORK *init_network(int num_inputs, int num_layers, int *num_inputs_per_layer, int batch_size);
double *get_total_loss(NETWORK *n, double **samples, double **ideal, int nsamples);
double *get_y(NETWORK *n, int layer_index, double *sample);
double *get_z(NETWORK *n, int layer_index, double *sample);
uint8_t **read_image_data(const char *filename, int *num_rows, const int num_cols);
double sse(double *real, double *ideal, int length);
void accumulate_layer_gradients(LAYER *l, int batch_size);
void apply_gradients(NETWORK* n, int batch_size);
void multiply_matrix(const double *A, const double *B, double *C, int rows_a, int cols_a, int cols_b);
void transpose_matrix(const double *A, double *C, int rows, int cols);

// utility functions
void free_layer(LAYER *l);
void free_network(NETWORK *n);
void free_neuron(NEURON *n);
void free_double_matrix(double **addr, int nrows);
void free_uint8_matrix(uint8_t **addr, int nrows);
void print_double_matrix(double **addr, int nrows, int ncols);
void print_double_vector(double *addr, int nrows);

#endif
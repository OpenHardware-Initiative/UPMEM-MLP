#ifndef MNIST_H
#define MNIST_H

#ifndef NUM_TRAIN_SAMPLES
#define NUM_TRAIN_SAMPLES 60000
#endif

#define NUM_LABELS 10
#define NUM_FEATURES (28*28)

#ifndef TRAINING_IMAGES_FILE
#define TRAINING_IMAGES_FILE "training_images.txt"
#endif

#ifndef TRAINING_LABELS_FILE
#define TRAINING_LABELS_FILE "training_labels.txt"
#endif

#endif
# UPMEM-MLP

## Summary

UPMEM-MLP is an attempt at implementing a dependency-free multilayer perceptron application in pure C and accelerating this application on the UPMEM platform.

## Running the Unit Tests

To run the CMake test flow:

```bash
mkdir build
cd build
cmake ..
make
make test
```

## Running the Multilayer Perceptron Natively

To run the C multilayer perceptron implementation:

1. Navigate to the source directory (`cd src`)
2. Compile the application:

```bash
gcc -I../include *.c -o mlp -lm
```

To compile in `DEBUG` mode (which offers a more detailed printout to stdout):

```bash
gcc -DDEBUG -I../include *.c -o mlp -lm
```

## Status

UPMEM-MLP is a work in progress as of 2025-10-19.

### To-Do:

- [] Fix memory leaks
- [] Introduce batch processing
- [] Adapt `src/get_z` for in-memory matrix multiplication on UPMEM

## License

UPMEM-MLP is licensed under the Apache License v2.0. See [LICENSE](LICENSE) for more details.

---
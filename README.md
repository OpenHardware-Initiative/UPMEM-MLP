# UPMEM-MLP

UPMEM-MLP is an attempt at implementing a multilayer perceptron application in pure C and accelerating this application on the UPMEM platform.

## Requirements

- GCC or Clang
- CMake 3.10 or higher
- UPMEM SDK

## Installing UPMEM SDK

To set up the UPMEM SDK on your system:

1. Download UPMEM SDK tarball for your system from [this link](https://sdk.upmem.com/)

2. Extract its content and (preferably) move it to a better place like `/usr/local/bin/`

3. Add the shell script `upmem_env.sh`, which sets necessary environment variables, to be sourced into your `.bashrc` as in:

```bash
source /usr/local/bin/upmem-sdk/upmem_env.sh > /dev/null
```

4. Restart your shell session for the changes to become effective

5. Test your setup using:

```bash
which dpu-lldb
```

which should, if correctly installed, return the path to the LLDB Debugger binary of UPMEM SDK

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

1. Navigate to the source directory:

```bash
cd src
```

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

### To-Do

- [ ] Fix memory leaks
- [ ] Introduce batch processing
- [ ] Adapt `src/get_z` for in-memory matrix multiplication on UPMEM

## License

UPMEM-MLP is licensed under the Apache License v2.0. See [LICENSE](LICENSE) for more details.

---
# UPMEM-MLP

UPMEM-MLP is an attempt at implementing a multilayer perceptron application in pure C and accelerating this application on the UPMEM platform.

[![Unit Tests](https://github.com/OpenHardware-Initiative/UPMEM-MLP/actions/workflows/unit_tests.yaml/badge.svg)](https://github.com/OpenHardware-Initiative/UPMEM-MLP/actions/workflows/unit_tests.yaml) [![Valgrind](https://github.com/OpenHardware-Initiative/UPMEM-MLP/actions/workflows/valgrind.yaml/badge.svg)](https://github.com/OpenHardware-Initiative/UPMEM-MLP/actions/workflows/valgrind.yaml)

## Requirements

- GCC or Clang
- CMake 3.10 or higher
- UPMEM SDK

### Installing UPMEM SDK

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

## Compiling the Multilayer Perceptron Natively

To natively run the C multilayer perceptron on your system:

1. Create a Python virtual environment (optional, but recommended) and install requirements:

```bash
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
```

2. Extract training samples & labels:

```bash
python3 read_dataset.py
```

3. Compile the application:

```bash
gcc -Iinclude src/*.c -o mlp -lm
```

With this command, you can use:

- `-DDEBUG` for the debug mode, which delivers a richer printout
- `-DBATCH_SIZE=...` to configure the batch size used during training
- `-DMAX_EPOCH=...` to configure the maximum number of epochs the training can run for
- `-DEPSILON=...` to configure EPSILON from the command line
- `-DNUM_TRAIN_SAMPLES=...` to configure from the command line how many samples the model should be trained with
- `-DTRAINING_IMAGES_FILE=...` to configure the path to the text file samples should be sourced from
- `-DTRAINING_LABELS_FILE=...` to configure the path to the text file labels should be sourced from

## Status

UPMEM-MLP is a work in progress as of 2025-11-14.

### To-Do

- [ ] Adapt `src/get_z` for in-memory matrix multiplication on UPMEM

## License

UPMEM-MLP is licensed under the Apache License v2.0. See [LICENSE](LICENSE) for more details.

---
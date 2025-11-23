# UPMEM-MLP

UPMEM-MLP implements a multilayer perceptron training application in C and accelerates this application on the UPMEM platform.

[![Unit Tests](https://github.com/OpenHardware-Initiative/UPMEM-MLP/actions/workflows/unit_tests.yaml/badge.svg)](https://github.com/OpenHardware-Initiative/UPMEM-MLP/actions/workflows/unit_tests.yaml) [![Memory Leak Tests](https://github.com/OpenHardware-Initiative/UPMEM-MLP/actions/workflows/memory_leak_tests.yaml/badge.svg)](https://github.com/OpenHardware-Initiative/UPMEM-MLP/actions/workflows/memory_leak_tests.yaml)

## Prerequisites

- CMake 3.10 or higher
- GCC
- Python
- UPMEM SDK

<details>
<summary><b>Installing UPMEM SDK</b></summary><br>

1. Download UPMEM SDK tarball for your system from [this link](https://github.com/kagandikmen/upmem-sdk)

> **NOTICE:** UPMEM SDK is no longer downloadable on UPMEM's official SDK [Downloads](https://sdk.upmem.com) page.

2. Extract its content and (preferably) move it to a better place like `/usr/local/bin/`

3. Add the shell script `upmem_env.sh`, which sets necessary environment variables, to be sourced into your `.bashrc`:

```bash
source /usr/local/bin/upmem-sdk/upmem_env.sh simulator > /dev/null
```

4. Restart your shell session for the changes to become effective

5. Test your setup:

```bash
which dpu-lldb
```
---
</details>

## Getting Started

1. Clone this repository and navigate inside it:

```bash
git clone https://github.com/OpenHardware-Initiative/UPMEM-MLP.git
cd UPMEM-MLP
```

2. **(Optional, but recommended)** Create a Python virtual environment:

```bash
python3 -m venv venv
source venv/bin/activate
```

3. Install Python requirements:

```bash
pip install -r requirements.txt
```

4. Extract training samples & labels:

```bash
python3 read_dataset.py
```

5. Compile the MLP:

```bash
make
```

6. Run the MLP:

```bash
./build/mlp
```

With this command, you can use:

- `BATCH_SIZE=...` to configure the batch size used during training, which otherwise defaults to 20
- `MAX_EPOCH=...` to configure the maximum number of epochs the training can run for, which otherwise defaults to 10
- `NUM_TRAIN_SAMPLES=...` to configure from the command line how many samples the model should be trained with, which otherwise defaults to 200
- `UPMEM=0` to turn off matrix multiplication on UPMEM
- `SAN=1` to run the MLP with GCC sanitizer
- `EVAL=1` to run the MLP in evaluation mode, which adds to the printout how many cycles are spent in training

## Running the Unit Tests

UPMEM-MLP comes with unit tests, which can be found in `tests/`. Run these unit tests using:

```bash
mkdir build
cd build
cmake ..
make
make test
```

## Status

UPMEM-MLP is completed and being actively maintained as of 2025-11-23.

## License

UPMEM-MLP is licensed under the Apache License v2.0. See [LICENSE](LICENSE) for more details.

---

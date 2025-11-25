# Benchmark Results

## NN Layout: NUM_FEATURES -> 4096 -> 4096 -> 2048 -> NUM_LABELS

| BATCH_SIZE | NUM_TRAIN_SAMPLES | MAX_EPOCH | Cycles (Intel 64 Host) | Cycles (Intel 64 Host + UPMEM) |
|------------|-------------------|-----------|------------------------|--------------------------------|
| 1200       | 3600              | 1         | 13.05T                 | 12.73T                         |
| 3600       | 10800             | 1         | 42.38T                 | 39.49T                         |
| 10800      | 32400             | 1         | 141.63T                | 129.94T                        |

---

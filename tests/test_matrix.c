#include "mlp.h"
#include "test.h"
#include "upmem.h"

int test_multiply_matrix()
{
    int test_result_pass_fail = 1;

    float matrixA[2*3] = {1.0, 2.0, 3.0, 
                           0.0, 5.0, 6.0};
    
    float matrixB[3*2] = {2.0, 6.0,
                           3.0, 3.0,
                           4.0, 0.0};
    
    // result matrices (initialized with random float values [0.0, 20.0])
    float matrixC[2*2];
    float matrixD[2*2];
    for(int i=0; i<2*2; i++) {
        matrixC[i] = ((float)rand() / (float)RAND_MAX) * 20;
        matrixD[i] = ((float)rand() / (float)RAND_MAX) * 20;
    }
    
    // ideal result
    float matrixR[2*2] = {20.0, 12.0,
                           39.0, 15.0};

    multiply_matrix_naive(matrixA, matrixB, matrixC, 2, 3, 2);

    init_dpus();
    multiply_matrix_upmem(matrixA, matrixB, matrixD, 2, 3, 2);
    free_dpus();

    for(int i=0; i<2*2; i++) {
        printf("%f ", matrixC[i]);
    }

    for(int i=0; i<2*2; i++) {
        test_result_pass_fail &= matrixC[i] == matrixR[i];
        test_result_pass_fail &= matrixC[i] == matrixD[i];
    }

    return test_result_pass_fail;
}

int test_transpose_matrix()
{
    int test_result_pass_fail = 1;

    float matrixA[2*3] = {1.0, 2.0, 3.0, 
                           0.0, 5.0, 6.0};

    // result matrix (initialized with random float values [0.0, 20.0])
    float matrixT[3*2];
    for(int i=0; i<3*2; i++) {
        matrixT[i] = ((float)rand() / (float)RAND_MAX) * 20;
    }

    // ideal result
    float matrixR[3*2] = {1.0, 0.0,
                           2.0, 5.0,
                           3.0, 6.0};

    transpose_matrix(matrixA, matrixT, 2, 3);

    for(int i=0; i<2*3; i++) {
        test_result_pass_fail |= matrixT[i] == matrixR[i];
    }

    return test_result_pass_fail;
}

int main()
{
    int test_pass_fail = 1;

    test_pass_fail |= test_multiply_matrix();
    test_pass_fail |= test_transpose_matrix();

    TEST_PASS_FAIL(test_pass_fail)
}
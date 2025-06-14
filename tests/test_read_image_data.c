#include "mlp.h"
#include "test.h"

int test_read_image_data()
{
    int ROWS;
    int COLS = 5;
    uint8_t **data = read_image_data("../tests/test_read_image_data.txt", &ROWS, COLS);
    return (data[0][0] == 5) && (data[0][1] == 6) && (data[1][0] == 7) && (data[1][1] == 8);;
}

int main()
{
    int test_pass_fail = test_read_image_data();

    TEST_PASS_FAIL(test_pass_fail)
}
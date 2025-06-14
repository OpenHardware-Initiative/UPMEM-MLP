#ifndef TEST_H
#define TEST_H

#define TEST_PASS_FAIL(test_result) \
if(test_result == 0) \
{ \
    printf("FAIL\n"); \
    return 1; \
} \
\
printf("PASS\n"); \
return 0; \

#endif
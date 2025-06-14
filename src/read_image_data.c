#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>      // for size_t and ssize_t

#include "mlp.h"

uint8_t **read_image_data(const char* filename, int *num_rows, const int num_cols)
{
    FILE *file = fopen(filename, "r");
    if(NULL == file)
    {
        fprintf(stderr, "Error 10001\n");
        return NULL;
    }

    uint8_t **data = NULL;
    *num_rows = 0;

    char *line = NULL;
    size_t line_size = 0;
    ssize_t chars_read = 0;

    while((chars_read = getline(&line, &line_size, file)) != -1)
    {
        // if(line[0] == "#")
        //     continue;

        data = realloc(data, (*num_rows+1)*sizeof(uint8_t*));
        if(NULL == data)
        {
            fprintf(stderr, "Error 10002\n");
            return NULL;
        }

        data[*num_rows] = malloc(num_cols*sizeof(uint8_t));
        if(NULL == data[*num_rows])
        {
            fprintf(stderr, "Error 10003\n");
            return NULL;
        }

        char *token = strtok(line, " ");
        int col = 0;
        while(token && col<num_cols)
        {
            data[*num_rows][col] = strtoul(token, NULL, 10);
            token = strtok(NULL, " ");
            ++col;
        }

        ++(*num_rows);
    }

    fclose(file);

    return data;
}
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>      // for size_t and ssize_t

uint8_t **read_image_data(const char* filename, int *ROWS, int COLS)
{
    FILE *file = fopen(filename, "r");
    if(NULL == file)
    {
        fprintf(stderr, "Error 10001\n");
        return NULL;
    }

    uint8_t **data = NULL;
    *ROWS = 0;

    char *line = NULL;
    size_t line_size = 0;
    ssize_t chars_read = 0;

    while((chars_read = getline(&line, &line_size, file)) != -1)
    {
        // if(line[0] == "#")
        //     continue;

        data = realloc(data, (*ROWS+1)*sizeof(uint8_t*));
        if(NULL == data)
        {
            fprintf(stderr, "Error 10002\n");
            return NULL;
        }

        data[*ROWS] = malloc(COLS*sizeof(uint8_t));
        if(NULL == data[*ROWS])
        {
            fprintf(stderr, "Error 10003\n");
            return NULL;
        }

        char *token = strtok(line, " ");
        int col = 0;
        while(token && col<COLS)
        {
            data[*ROWS][col] = strtoul(token, NULL, 10);
            token = strtok(NULL, " ");
            ++col;
        }

        ++(*ROWS);
    }

    fclose(file);

    return data;
}
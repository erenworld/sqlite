/*
** EREN TURKOGLU, 2025
** sqlite
** File description:
** main
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer *new_input_buffer()
{
    InputBuffer *input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));

    if (!input_buffer)
        exit(EXIT_FAILURE);
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}

static void print_prompt(void)
{
    printf("db > ");
}

static void close_input_buffer(InputBuffer *input_buffer)
{
    if (!input_buffer)
        return;
    free(input_buffer->buffer);
    free(input_buffer);
}

static void read_input(InputBuffer *input_buffer)
{
    // getline alloue automatiquement le buffer si NULL, et le remplit depuis stdin
    ssize_t bytes_read = getline(
                        &(input_buffer->buffer),
                        &(input_buffer->buffer_length),
                        stdin);
    
    if (bytes_read <= 0) {
        perror("getline");
        exit(EXIT_FAILURE);
    }
    // ignore trailine newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

int main(int argc, char *argv[])
{
    InputBuffer *input_buffer = new_input_buffer();

    while (true) {
        print_prompt();
        read_input(input_buffer);
        if (strcmp(input_buffer->buffer, ".exit") == 0) {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
    }
}

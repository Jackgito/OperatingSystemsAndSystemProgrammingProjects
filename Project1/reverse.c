#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 1024

void reverseAndPrint(FILE *input, FILE *output) {
    int INITIAL_BUFFER_SIZE = 100;
    char **buffer = malloc(INITIAL_BUFFER_SIZE * sizeof(char *));
    int count = 0;

    for (int i = 0; i < INITIAL_BUFFER_SIZE; i++) {
        buffer[i] = malloc(LINE_SIZE * sizeof(char));
    }

    char line[LINE_SIZE];

    while (fgets(line, LINE_SIZE, input) != NULL && line[0] != '\n') {
        if (count >= INITIAL_BUFFER_SIZE) {
            // Resize the buffer if more memory is needed
            INITIAL_BUFFER_SIZE *= 2;
            buffer = realloc(buffer, INITIAL_BUFFER_SIZE * sizeof(char *));
            for (int i = count; i < INITIAL_BUFFER_SIZE; i++) {
                buffer[i] = malloc(LINE_SIZE * sizeof(char));
            }
        }

        strcpy(buffer[count], line);
        count++;
    }

    // Write to the output file
    for (int i = count - 1; i >= 0; i--) {
        fprintf(output, "%s", buffer[i]);
    }

    // Free allocated memory
    for (int i = 0; i < count; i++) {
        free(buffer[i]);
    }
    free(buffer);
}

int main(int argc, char *argv[]) {
    // Check for the correct number of arguments
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    FILE *input = stdin;
    FILE *output = stdout;

    // Open input file if specified
    if (argc >= 2) {
        input = fopen(argv[1], "r");

        if (input == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }

    // Open output file if specified
    if (argc == 3) {
        output = fopen(argv[2], "w");

        if (output == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);

            // Close the input file if it was opened
            if (argc >= 2) {
                fclose(input);
            }

            exit(1);
        }

        // Check if input and output files are the same
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "Input and output file must differ\n");

            // Close the files if they were opened
            fclose(input);
            fclose(output);

            exit(1);
        }
    }

    reverseAndPrint(input, output);

    // Close the files if they were opened
    if (argc >= 2) {
        fclose(input);
    }
    if (argc == 3) {
        fclose(output);
    }

    return 0;
}

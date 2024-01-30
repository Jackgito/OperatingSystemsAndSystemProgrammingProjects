#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to find string from file(s)
void grepInFile(const char *searchTerm, const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "my-grep: cannot open file\n");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        if (strstr(line, searchTerm) != NULL) {
            printf("%s", line);
        }
    }

    fclose(file);
    free(line);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    }

    const char *searchTerm = argv[1];

    if (argc == 2) {
        // Read from standard input
        char *line = NULL;
        size_t len = 0;

        while (getline(&line, &len, stdin) != -1) {
            if (strstr(line, searchTerm) != NULL) {
                printf("%s", line);
            }
        }

        free(line);
    } else {
        // Read from files
        for (int i = 2; i < argc; i++) {
            grepInFile(searchTerm, argv[i]);
        }
    }

    exit(0);
}

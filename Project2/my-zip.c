#include <stdio.h>
#include <stdlib.h>

void compressFile(FILE *file) {
    int count = 1;
    char current_char, next_char;

    while (fread(&next_char, sizeof(char), 1, file) > 0) {
        if (next_char == current_char) {
            count++;
        } else {
            fwrite(&count, sizeof(int), 1, stdout);
            fwrite(&current_char, sizeof(char), 1, stdout);
            count = 1;
            current_char = next_char;
        }
    }

    // Output the last run
    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&current_char, sizeof(char), 1, stdout);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "my-zip: cannot open file '%s'\n", argv[i]);
            exit(1);
        }

        compressFile(file);

        fclose(file);
    }

    exit(0);
}

#include <stdio.h>
#include <stdlib.h>

void decompressFile(FILE *file) {
    int count;
    char current_char;

    while (fread(&count, sizeof(int), 1, file) > 0) {
        fread(&current_char, sizeof(char), 1, file);
        for (int i = 0; i < count; i++) {
            printf("%c", current_char);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "my-unzip: cannot open file '%s'\n", argv[i]);
            exit(1);
        }

        decompressFile(file);

        fclose(file);
    }

    exit(0);
}

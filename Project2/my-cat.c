#include <stdio.h>
#include <stdlib.h>

void printFileContents(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "my-cat: cannot open file\n");
        exit(1);
    }

    // Print one character at a time
    int c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // No files specified, just exit
        exit(0);
    }

    for (int i = 1; i < argc; i++) {
        printFileContents(argv[i]);
    }

    exit(0);
}

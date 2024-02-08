#include <stdio.h>
#include <stdlib.h>

// Function to decompress the contents of a file
void decompressFile(FILE *file) {
    int count;
    char current_char;

    // Read the count of characters and the character itself from the file
    while (fread(&count, sizeof(int), 1, file) > 0) {
        fread(&current_char, sizeof(char), 1, file);

        // Print the character 'count' number of times
        for (int i = 0; i < count; i++) {
            printf("%c", current_char);
        }
    }
}

// Main function
int main(int argc, char *argv[]) {
    // Check if the correct number of command line arguments is provided
    if (argc < 2) {
        fprintf(stderr, "Usage: my-unzip file1 [file2 ...]\n");
        exit(1);
    }

    // Loop through each file provided as a command line argument
    for (int i = 1; i < argc; i++) {
        // Open the file in read-only mode
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

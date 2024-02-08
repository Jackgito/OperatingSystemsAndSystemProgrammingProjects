#include <stdio.h>
#include <stdlib.h>

// Function to compress the contents of a file
void compressFile(FILE *file) {
    int count = 1;  // Initialize the count of consecutive characters
    char current_char, next_char;

    // Read characters from the file until the end is reached
    while (fread(&next_char, sizeof(char), 1, file) > 0) {
        // Check if the current character is the same as the next character
        if (next_char == current_char) {
            count++;    // Increment the count if characters are the same
        } else {
            // Write the count and the current character to the standard output
            fwrite(&count, sizeof(int), 1, stdout);
            fwrite(&current_char, sizeof(char), 1, stdout);

            // Reset count and update the current character
            count = 1;
            current_char = next_char;
        }
    }

    // Output the last run of characters
    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&current_char, sizeof(char), 1, stdout);
}

// Main function
int main(int argc, char *argv[]) {
    // Check if the correct number of command line arguments is provided
    if (argc < 2) {
        fprintf(stderr, "Usage: my-zip file1 [file2 ...]\n");
        exit(1);
    }

    // Loop through each file provided as a command line argument
    for (int i = 1; i < argc; i++) {
        // Open the file in read-only mode
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

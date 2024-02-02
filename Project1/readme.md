# Reverse Program

This project involves the creation of a simple C program named `reverse` that reverses the order of lines in a file or from standard input. The program can be invoked with various command-line arguments to control input and output.

## Usage

The `reverse` program can be invoked in the following ways:

1. Without any command-line arguments:

    ```bash
    prompt> ./reverse
    ```

   Reads from standard input and prints the reversed lines to standard output.

2. With one command-line argument (input file):

    ```bash
    prompt> ./reverse input.txt
    ```

   Reads from the specified input file and prints the reversed lines to standard output.

3. With two command-line arguments (input and output files):

    ```bash
    prompt> ./reverse input.txt output.txt
    ```

   Reads from the input file and writes the reversed lines to the specified output file.

## Details

### Assumptions and Errors

- **Input is the same as output:**
  If the input file and output file are the same, the program prints an error message and exits with return code 1.

- **String length:**
  The program does not assume anything about the length of a line. It can handle very long input lines.

- **File length:**
  The program does not assume anything about the length of the file. It is designed to handle very long files.

- **Invalid files:**
  If the specified input or output file cannot be opened, the program prints an error message and exits with return code 1.

- **Malloc fails:**
  If malloc fails during memory allocation, the program prints an error message and exits with return code 1.

- **Too many arguments:**
  If the user provides too many arguments, the program prints a usage message and exits with return code 1.

### Error Message Format

On encountering any error, the program prints the error to the screen using `fprintf()` and sends the error message to stderr (standard error) using the following format:

```c
fprintf(stderr, "error: <error message>\n");
```

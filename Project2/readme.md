# Unix Utilities

This project involves the implementation of several simplified UNIX utilities in the C programming language. Each utility has a specific purpose and corresponds to commonly used commands like `cat`, `grep`, `zip`, and `unzip`. The goal is to re-familiarize oneself with C programming, UNIX command-line interfaces, and basic file manipulation.

## Utilities Overview

### `my-cat`

The `my-cat` utility reads a file specified by the user and prints its contents. It can be invoked as follows:

```bash
prompt> ./my-cat main.c
```

- **Usage:**
  ```bash
  ./my-cat file1 [file2 ...]
  ```

- **Behavior:**
  - Prints the contents of each specified file.
  - Exits with status code 1 if it encounters an error opening a file.

### `my-grep`

The `my-grep` utility searches for a user-specified search term in one or more files, printing lines containing the term.

```bash
prompt> ./my-grep search_term file1 [file2 ...]
```

- **Behavior:**
  - Prints lines containing the specified search term.
  - Case-sensitive matching.
  - Exits with status code 1 if no command-line arguments are provided or encounters an error opening a file.

### `my-zip` and `my-unzip`

These utilities form a pair for file compression and decompression using a simple run-length encoding (RLE) scheme.

#### `my-zip`

The `my-zip` utility compresses files using RLE and writes the compressed output to standard output.

```bash
prompt> ./my-zip file1 [file2 ...] > compressed_file.z
```

- **Behavior:**
  - Compresses files using RLE encoding.
  - Outputs compressed data to standard output.

#### `my-unzip`

The `my-unzip` utility decompresses files previously compressed with `my-zip` and prints the uncompressed output to standard output.

```bash
prompt> ./my-unzip compressed_file.z
```

- **Behavior:**
  - Decompresses files using RLE encoding.
  - Prints the uncompressed data to standard output.


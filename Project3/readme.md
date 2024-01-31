# Simple Shell Program

This is a simple shell program written in C that provides a basic command-line interface. The shell supports commands like changing directories (`cd`), managing the command path (`path`), and executing external commands with input/output redirection.

## Usage

1. **Compilation:**
   ```bash
   gcc main.c shell_functions.c -o my_shell
   ```

2. **Execution:**
   ```bash
   ./my_shell
   ```

3. **Commands:**
   - **`cd` Command:**
     ```bash
     cd [directory]
     ```
     Change the current working directory.

   - **`path` Command:**
     ```bash
     path [directory1 directory2 ...]
     ```
     Update the path for executable file lookup.

   - **`exit` Command:**
     ```bash
     exit
     ```
     Exit the shell.

   - **Other Commands:**
     Any other commands entered in the shell will be executed, supporting input/output redirection.

## Features

- **Path Management:**
  - Use the `path` command to specify directories where the shell should look for executable files.

- **Change Directory:**
  - Use the `cd` command to change the current working directory.

- **Input/Output Redirection:**
  - Redirect command output (`>`) or input (`<`) as needed.

## Functions

- **`handle_error`:**
  - Display error messages to stderr.

- **`string_break`:**
  - Tokenize a user input line for further processing.

- **`print_tokens`:**
  - Print an array of tokens.

- **`update_path`:**
  - Update the 'path' variable based on user input.

- **`change_directory`:**
  - Change the current working directory.

- **`check_redirection`:**
  - Check if input contains output/input redirection symbols ('>' or '<').

- **`get_path`:**
  - Construct the full path for execution based on the given path variable.

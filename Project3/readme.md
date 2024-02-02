# Simple Unix Shell (wish)

This is a simple Unix shell named `wish` that provides basic command-line interpreter functionality. The shell supports several features, including path management, built-in commands (`exit`, `cd`, `path`), input/output redirection, and parallel command execution.

## Program Specifications

### Basic Shell: `wish`

The basic shell, `wish` (Wisconsin Shell), operates interactively in a loop. It prints a prompt (`wish>`) and allows users to enter commands. The shell creates a child process for each command entered, executes the command, and waits for its completion. The loop continues until the user types `exit`.

## Usage

1. Run the shell interactively:

   ```bash
   ./wish
   ```

2. Run the shell in batch mode:

   ```bash
   ./wish < batch.txt
   ```


### Features

1. **Built-in Commands:**
   - `exit`: Exits the shell.
   - `cd`: Changes the current working directory.
   - `path`: Updates the search path for executables.

2. **Path Management:**
   - The shell maintains a path variable to specify directories to search for executables.
   - The `path` command updates the search path.

3. **Redirection:**
   - Supports output redirection (`>`) to redirect the standard output to a file.
   - Supports input redirection (`<`) to read input from a file.

4. **Parallel Commands:**
   - Allows launching parallel commands using the ampersand (`&`) operator.

5. **Advanced Error Handling**
   - Descriptive errors for many situations

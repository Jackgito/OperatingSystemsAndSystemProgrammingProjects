// Shell template was taken from: https://github.com/tanishqjasoria/wish

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "shell_functions.h"

char *path[10];

int main()
{
  char *line = NULL;
  size_t input_size = 0;
  char *input_tokens[10];

  int in_out;
  char *redirection_file;

  while (1)
  {
    printf("wish> ");

    // Use getline function to read the input from the user, it is a
    // blocking syscall
    int res = getline(&line, &input_size, stdin);

    // End of File
    if (res == -1)
      exit(0);

    if (res == 1)
      // If the input string only contains '\n' char, this implies
      // an empty string, which might just return the prompt to the user
      continue;
    else
    {
      int input_len = string_break(line, input_tokens);

      // Path
      if (strcmp(input_tokens[0], "path") == 0)
      {
        // Update the 'path' variable with user-specified paths
        update_path(input_tokens + 1);
        print_tokens(path);
        continue;
      }

      // CD
      if (strcmp(input_tokens[0], "cd") == 0)
      {
        // Change the current working directory if 'cd' command is used
        if (input_len > 2)
        {
          // Exit if invalid 'cd' command
          handle_error("Invalid 'cd' command\n");
          exit(1);
        }
        change_directory(input_tokens + 1);
        continue;
      }

      // Exit
      if (strcmp(input_tokens[0], "exit") == 0)
      {
        // Exit the shell if 'exit' command is encountered
        exit(0);
      }

      int redirection_index = check_redirection(input_tokens, &in_out);

      if ((input_len > redirection_index + 2) && (in_out != 0))
      {
        // Exit if invalid usage of input/output redirection symbols
        handle_error("Invalid input/output redirection\n");
        exit(1);
      }
      else
      {
        redirection_file = input_tokens[redirection_index + 1];
        input_tokens[redirection_index] = NULL;
      }

      int ret = get_path(input_tokens);
      if (ret == -1)
      {
        // Exit if the executable is not found in specified paths
        handle_error("Executable not found in specified paths\n");
        exit(1);
      }

      int rc = fork();
      if (rc < 0)
      {
        // Exit if fork fails
        handle_error("Fork failed\n");
        exit(1);
      }
      else if (rc == 0)
      {
        // When a child is created using the fork call, the value
        // returned is 0.

        // Handle output redirection
        if (in_out == 1)
        {
          int fd = creat(redirection_file, 0644);
          dup2(fd, STDOUT_FILENO);
          dup2(fd, STDERR_FILENO);
          close(fd);
        }
        // Handle input redirection
        else if (in_out == 2)
        {
          int fd = open(redirection_file, O_RDONLY);
          dup2(fd, STDIN_FILENO);
          close(fd);
        }

        // Execute the command in the child process
        int ret_exec = execv(input_tokens[0], input_tokens);
        if (ret_exec == -1)
        {
          // Exit if execv fails
          handle_error("Execv failed\n");
          exit(1);
        }
      }
      else
      {
        // Wait for the child process to finish
        wait(NULL);
      }
    }
  }
}

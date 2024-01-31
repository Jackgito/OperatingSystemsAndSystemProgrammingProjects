#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

char *path[10];

// Function to print an error message to stderr
void handle_error(const char *error_message)
{
  write(STDERR_FILENO, error_message, strlen(error_message));
}

// Function to tokenize a user input line for further processing
int string_break(char *line, char *tokens[])
{
  int i = 0;
  const char delimiter = ' ';
  // Remove the trailing '\n', if any
  strtok(line, "\n");
  while (1)
  {
    // Break the user input into tokens using a fixed delimiter
    tokens[i] = strsep(&line, &delimiter);
    if (tokens[i] == NULL)
      break;
    i++;
  }
  return i;
}

// Function to print an array of tokens
void print_tokens(char *tokens[])
{
  int i = 0;
  while (1)
  {
    if (tokens[i] == NULL)
    {
      printf("\n");
      break;
    }
    else
    {
      printf("%s ", tokens[i]);
    }
    i++;
  }
}

// Function to update the 'path' variable based on user input
void update_path(char *tokens[])
{
  int i = 0;
  while (1)
  {
    if (tokens[i] == NULL)
    {
      path[i] = NULL;
      break;
    }
    else
    {
      // Allocate memory for each path element and copy the content
      path[i] = (char *)malloc(strlen(tokens[i]) + 1);
      if (path[i] == NULL)
      {
        handle_error("Memory allocation error\n");
        exit(1);
      }
      strcpy(path[i], tokens[i]);
    }
    i++;
  }
}

// Function to change the current working directory
void change_directory(char *token[])
{
  if (chdir(token[0]) == -1)
  {
    handle_error("Error changing directory\n");
    exit(1);
  }
}

// Function to check if input contains output/input redirection symbols ('>' or '<')
int check_redirection(char *tokens[], int *in_out)
{
  int i = 0;

  while (1)
  {
    if (tokens[i] == NULL)
      break;
    if (strcmp(tokens[i], ">") == 0)
    {
      // Set in_out variable to indicate output redirection
      *in_out = 1;
      return i;
    }
    if (strcmp(tokens[i], "<") == 0)
    {
      // Set in_out variable to indicate input redirection
      *in_out = 2;
      return i;
    }
    i++;
  }
  // No redirection symbols found
  *in_out = 0;
  return -1;
}

// Function to construct the full path for execution based on the given path variable
int get_path(char *tokens[])
{
  char temp_path[20];

  int i = 0;
  while (1)
  {
    if (path[i] == NULL)
      break;
    else
    {
      // Construct a potential full path for executable file
      strcpy(temp_path, path[i]);
      strcat(temp_path, tokens[0]);
      int ret_access = access(temp_path, X_OK);
      if (ret_access == 0)
      {
        // Update the token with the full path if executable is found
        tokens[0] = (char *)malloc(strlen(temp_path) + 1);
        if (tokens[0] == NULL)
        {
          handle_error("Memory allocation error\n");
          exit(1);
        }
        strcpy(tokens[0], temp_path);
        return 0;
      }
    }
    i++;
  }
  // Executable not found in the specified paths
  return -1;
}
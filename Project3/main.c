#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_PATHS 10
#define MAX_TOKENS 10

char *path[MAX_PATHS];

// Function to break a string into tokens
int tokenize_string(char *user_input, char *tokens[]) {
    int token_count = 0;
    const char delimiter = ' ';

    // Remove the trailing '\n', if any
    strtok(user_input, "\n");

    while (1) {
        // Break the user input into tokens using a fixed delimiter
        tokens[token_count] = strsep(&user_input, &delimiter);
        if (tokens[token_count] == NULL)
            break;
        token_count++;
    }
    return token_count;
}

// Function to update the 'path' variable with user-specified paths
void update_path(char *tokens[]) {
    int i = 0;
    while (tokens[i] != NULL) {
        if (i >= MAX_PATHS) {
            fprintf(stderr, "Error: Too many paths specified\n");
            exit(EXIT_FAILURE);
        }

        if (tokens[i] == NULL) {
            path[i] = NULL;
            break;
        } else {
            path[i] = (char *)malloc(strlen(tokens[i]) + 1);
            strcpy(path[i], tokens[i]);
        }
        i++;
    }

    // Print the updated path
    printf("Updated path:");
    for (int j = 0; j < i; j++) {
        printf(" %s", path[j]);
    }
    printf("\n");
}


// Function to change the current working directory
void change_directory(char *token[]) {
    if (token[1] != NULL) {
        fprintf(stderr, "cd: Too many arguments\n");
        return;
    }

    if (chdir(token[0]) == -1) {
        perror("cd");
    } else {
        // Get and print the current directory after successful change
        char current_directory[5000];
        if (getcwd(current_directory, sizeof(current_directory)) != NULL) {
            printf("Current directory: %s\n", current_directory);
        } else {
            perror("getcwd");
        }
    }
}

// Function to check for input/output redirection
int check_redirection(char *tokens[], int *in_out) {
    int i = 0;
    while (tokens[i] != NULL) {
        if (strcmp(tokens[i], ">") == 0) {
            *in_out = 1;
            return i;
        }
        if (strcmp(tokens[i], "<") == 0) {
            *in_out = 2;
            return i;
        }
        i++;
    }
    *in_out = 0;
    return -1;
}

// Function to construct a full path by combining paths from 'path' array and the executable name
int construct_full_path(char *tokens[]) {
    char temp_path[256];

    int i = 0;
    while (path[i] != NULL) {
        strcpy(temp_path, path[i]);
        strcat(temp_path, "/");
        strcat(temp_path, tokens[0]);
        if (access(temp_path, X_OK) == 0) {
            tokens[0] = (char *)malloc(strlen(temp_path) + 1);
            strcpy(tokens[0], temp_path);
            return 0;
        }
        i++;
    }
    return -1;
}

// Function to handle system commands
void execute_system_command(char *tokens[]) {
    int rc = fork();
    if (rc < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        // Child process
        int exec_result = execvp(tokens[0], tokens);
        if (exec_result == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        int status;
        waitpid(rc, &status, 0);
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) != 0) {
                fprintf(stderr, "Command failed with exit code %d\n", WEXITSTATUS(status));
            }
        } else if (WIFSIGNALED(status)) {
            fprintf(stderr, "Command terminated by signal %d\n", WTERMSIG(status));
        }
    }
}

int main() {
    char *user_input = NULL;
    size_t input_buffer_size = 0;
    char *tokens[MAX_TOKENS];

    int in_out;
    char *redirection_file;

    while (1) {
        printf("wish> ");

        // Use getline function to read the input from the user, it is a
        // blocking syscall
        int input_length = getline(&user_input, &input_buffer_size, stdin);

        // End of File
        if (input_length == -1)
            exit(EXIT_SUCCESS);

        if (input_length == 1)
            // If the input string only contains '\n' char, this implies
            // an empty string, which might just return the prompt to the user
            continue;
        else {
            int token_count = tokenize_string(user_input, tokens);

            if (strcmp(tokens[0], "path") == 0) {
                // Code for path command
                update_path(tokens + 1);
                continue;
            }

            if (strcmp(tokens[0], "cd") == 0) {
                // Code for cd command
                change_directory(tokens + 1);
                continue;
            }

            if (strcmp(tokens[0], "exit") == 0) {
                // Code for exit command
                exit(EXIT_SUCCESS);
            }

            int redirection_index = check_redirection(tokens, &in_out);

            if ((token_count > redirection_index + 2) && (in_out != 0)) {
                fprintf(stderr, "Error: Invalid input redirection\n");
                exit(EXIT_FAILURE);
            } else {
                redirection_file = tokens[redirection_index + 1];
                tokens[redirection_index] = NULL;
            }

            int ret = construct_full_path(tokens);

            if (ret == -1) {
                // If the command is not found in the specified path, try executing it as a system command
                execute_system_command(tokens);
                continue;
            }

            int process_id = fork();
            if (process_id < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (process_id == 0) {
                // When a child is created using the fork call, the value
                // returned is 0.
                if (in_out == 1) {
                    int file_descriptor = creat(redirection_file, 0644);
                    if (file_descriptor == -1) {
                        perror("creat");
                        exit(EXIT_FAILURE);
                    }
                    dup2(file_descriptor, STDOUT_FILENO);
                    dup2(file_descriptor, STDERR_FILENO);
                    close(file_descriptor);
                } else if (in_out == 2) {
                    int file_descriptor = open(redirection_file, O_RDONLY);
                    if (file_descriptor == -1) {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                    dup2(file_descriptor, STDIN_FILENO);
                    close(file_descriptor);
                }
                int exec_result = execv(tokens[0], tokens);
                if (exec_result == -1) {
                    perror("execv");
                    exit(EXIT_FAILURE);
                }
            } else {
                wait(NULL);
            }
        }
    }
}

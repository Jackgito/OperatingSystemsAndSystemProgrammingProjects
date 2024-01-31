// shell_functions.h

#ifndef SHELL_FUNCTIONS_H
#define SHELL_FUNCTIONS_H

void handle_error(const char *error_message);
int string_break(char *line, char *tokens[]);
void print_tokens(char *tokens[]);
void update_path(char *tokens[]);
void change_directory(char *token[]);
int check_redirection(char *tokens[], int *in_out);
int get_path(char *tokens[]);

#endif

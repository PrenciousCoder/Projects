#ifndef COMMANDS_H
#define COMMANDS_H

#define MAX_INPUT 1024
#define MAX_ARGS 64

void read_input(char *input);
void parse_input(char *input, char **args);
void execute_command(char **args);

#endif

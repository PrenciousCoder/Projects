#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

//!Function to read user input
void read_input(char *input) {
    printf("myshell> ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0;  // Remove newline character
}

//!Function to parse input into command and arguments
void parse_input(char *input, char **args) {
    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  // Null-terminate the argument list
}


//! Function for list directory
void list_directory(const char *path){
    DIR *dir=opendir(path); //? allows to read contents of a directory
    if(dir==NULL){
        perror("ls");
        return;
    }
    struct dirent *entry;
    while((entry=readdir(dir))!=NULL){
        printf("%s", entry->d_name);
    }
    printf("\n");
    closedir(dir);
}


// Function to execute commands
void execute_command(char **args) {
    if (args[0] == NULL) return;  // Empty command
    
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        }
        return;
    }
    else if(strcmp(args[0],"ls")==0){
        list_directory(args[1] ? args[1]:".");
        return;
    }
    
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("myshell");
        }
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        waitpid(pid, NULL, 0);
    } else {
        perror("fork");
    }
}

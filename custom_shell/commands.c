#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>


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

//! Echo function
void echo_command(char **args){
    for(int i =1;args[i]!=NULL;i++){
        printf("%s ",args[i]);
    }
    printf("\n");
}

//!Function to print current working directory
void prensent_working_directory(){
    char cwd[1024];
    if(getcwd(cwd,sizeof(cwd))!=NULL){
        printf("%s\n",cwd);
    }
    else{
        perror("pwd");
    }
}

//! Output redirection
void output_redirection(char **args){
    int i=0;
    int fd=-1;

    while(args[i]!=NULL){
        if(strcmp(args[i],">")==0){
            if(args[i+1]==NULL){
                fprintf(stderr,"Sytax error: No output file Specified\n");
                return;
            }
            fd=open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(fd==-1){
                perror("open");
                return;
            }

            //!Redirect output to the file
            if(dup2(fd,STDOUT_FILENO)==-1){
                perror("dup2");
                close(fd);
                return;
            }
            close(fd);

            //!Remove ">" and file name from args
            args[i]=NULL;
            break;
        }
        i++;
    }
}

//!Function to execute commands
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
    else if(strcmp(args[0],"pwd")==0){
        prensent_working_directory();
        return;
    }

    //!Execution of echo function
    else if(strcmp(args[0],"echo")==0){
        echo_command(args);
        return;
    }
    
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        output_redirection(args);
        
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

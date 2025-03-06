#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

//!Function to read the input from user
void read_input(char *input){
    printf("Custom_Shell>");
    fgets(input,MAX_INPUT,stdin);
    //!Remove newline character
    input[strcspn(input,"\n")]=0; //?Removing the newline character

}

//!Parsing function
void parse_input(char* input,char **args ){
    char *token=strtok(input, " "); //?Divide the striong into tokens using blankspace
    int i=0;
    while(token!=NULL && i<MAX_ARGS -1){
        args[i++]=token;
        token=strtok(NULL," "); //?Divide the string into tokens using blankspace
}
    args[i]=NULL; //?End of the array
    }

//! strcmp= function to compare two strings
void execute_command(char **args){
    if(args[0]==NULL){ //?Empty command case
        return;
    }
    if(strcmp(args[0],"exit")==0){
        exit(0);
    }
    else if(strcmp(args[0],"cd")==0){
        if(args[1]==NULL){
            fprintf(stderr, "cd: missing argument\n");
        }
        else{
            if(chdir(args[1])!=0){
                perror("cd");
            }
        }
        return;
    }
    pid_t pid=fork(); //? Fork= function to create a new process
    if(pid==0){ //?it means the code is executing in child process

        //!Child process
        if(execvp(args[0],args)==-1){
            perror("myshell");
        }
        exit(EXIT_FAILURE);
    }
    else if(pid>0){ //? Code is execeuting in parent process
        //!Parent process
        waitpid(pid,NULL,0);
    }
    else{
        perror("fork");
    }
}

int main(){
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    while(1){
        read_input(input);
        parse_input(input,args);
        execute_command(args);
    }
    return 0;
}
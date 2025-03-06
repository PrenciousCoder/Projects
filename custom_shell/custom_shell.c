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

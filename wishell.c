#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int BUFFER_SIZE = 256;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void tokenization(char str[BUFFER_SIZE]) {

    printf("tokenization function\n");
    printf("str = %s\n", str);

    char *token;
    char *argv[BUFFER_SIZE];
    int argc = 0;

    // Remove trailing newline (important if using fgets)
    str[strcspn(str, "\n")] = '\0';

    // Tokenize input
    token = strtok(str, " ");

    while (token != NULL && argc < BUFFER_SIZE - 1) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    // If no command entered
    if (argc == 0) {
        printf("No command entered\n");
        return;
    }

    // NULL terminate argument list (REQUIRED for execvp)
    argv[argc] = NULL;

    printf("Executing command: %s\n", argv[0]);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return;
    }

    if (pid == 0) {
        // Child process
        execvp(argv[0], argv);

        // If execvp returns, it failed
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } 
    else {
        // Parent process waits for child
        wait(NULL);
    }
}



int main(){
    
    while(1){
        printf("wishell>$ ");

        //command
        char command[BUFFER_SIZE];
        
        //read input from user
        fgets(command, BUFFER_SIZE, stdin);
        printf("command is %s\n", command);
        tokenization(command);
        printf("\n\n");

        printf("\n");
    }

}
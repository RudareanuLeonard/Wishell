#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int BUFFER_SIZE = 256;

void tokenization(char str[BUFFER_SIZE]){

    /*
    
    ls -la /my/folder
    so the command itself is "ls" and "-la" and /my/folder are arguemnts
    
    */

    printf("tokenization function\n");

    printf("str = %s\n", str);

    char *p;
    char *command = NULL; //stored as readonly and points to the beginning of the command
    __uint8_t did_command = 0;


    p = strtok(str, " ");
    printf("a\n");

    while(p != NULL){
        // printf("str = %s\n", p); <- this causes segfalut
        if(did_command == 0){
            printf("\n did_command just got value 1 \n");
            command = p; //address of p
            
            did_command = 1;
            
            //run fork to run command
            pid_t new_fork = fork(); // create this to make a child process of the shell
            execvp("echo", "asda");
        
        }
        p = strtok(NULL, " ");
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
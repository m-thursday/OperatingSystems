#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int number = strtol(argv[1], NULL, 10);
    if (number < 0){
        printf("value not applicable restart and try again");
        return 1;
    }
    printf("%d", number);
    printf("\n");
    pid_t pid;
    pid = fork();
    if (pid < 0){ // failed process
        printf("Fork Failed");
        return 1;
    }
    else if(pid == 0){ // child process
        while(number != 1){    
            if (number % 2 == 0){
                number = number / 2;
                printf("%d", number);
                printf(" ");
            }
            else{
                number = ((number * 3) + 1);
                printf("%d", number);
                printf(" ");
            }
        }
    }
    else{ // parent process
        wait(NULL);
        printf("\n");
        printf("Collatz sequence finished");
        printf("\n");
    }
}

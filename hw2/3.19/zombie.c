#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(){
    pid_t pid;

    pid = fork();

    if (pid < 0){ // failed process
        printf("Fork Failed");
        return 1;
    }
    else if(pid == 0){ // child process

        exit(0);
    
    }
    else{ // parent process
        sleep(15);
    }


}
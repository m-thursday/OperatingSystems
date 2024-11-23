#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

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

    const int SIZE = 4096;
    const char* name = "OS";
 
    int shm_fd;
    void* ptr;
    int add;

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

        while(number != 1){    
            if (number % 2 == 0){
                number = number / 2;
            }
            else{
                number = ((number * 3) + 1);
            }
            add = sprintf(ptr, "%d ", number);
            ptr += add;
        }
    }

    else{ // parent process
        wait(NULL);
        const int SIZE = 4096;
        const char* name = "OS";
        int shm_fd;
        void* ptr;
    
        shm_fd = shm_open(name, O_RDONLY, 0666);
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    
        printf("%s", (char*)ptr);
        shm_unlink(name);

        printf("\n");
        printf("Collatz sequence finished");
        printf("\n");
        return 0;
    }
}

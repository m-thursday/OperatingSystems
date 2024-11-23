

#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


#define READ_END 0
#define WRITE_END 1

int main(int argc, char* argv[]){
    // setup -------------------------------------------------
    int ffd[2];

    int fd1[2];
    pipe(fd1);

    ffd[READ_END] = open(argv[1], O_RDONLY);

    // Error Checking ---------------------------------------
    if (argc != 3){
        printf("Argument Error");
        return 1;
    }
    if(pipe(fd1) == -1){
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    if(ffd[1] < 0){
        printf("Error opening file/s");
        return 1;
    } // -----------------------------------------------------

    ffd[1] = open(argv[2], O_CREAT | O_RDWR, 0400 | 0200); // S_IRUSR | S_IWUSR

    // forking -----------------------------------------------
    pid_t pid;
    pid = fork();

    // Fork Failed -------------------------------------------
    if (pid < 0){ 
        perror("Fork failed");
    }

    // child process ------------------------------------------
    else if(pid == 0){ 
        char* readFile[2];
        char a;

        // closes the write end of the first pipe -------------
        close(fd1[1]);

        // child reads message from pipe ----------------------
        while (a = read(fd1[0], readFile, 1) > 0){
            write(ffd[1], readFile, 1);
        }

        close(fd1[0]);
        close(ffd[1]);

        return 0;
    }
    // parent process -----------------------------------------
    else{ 

        char* writeFile[2];
        char c;

       // close the read end of the first pipe ----------------
        close(fd1[0]);

        // takes file to copy and puts it into a string -------
        while ((c = read(ffd[0], writeFile, 1)) > 0){
            // parent writes message into pipe ---------------------
            write(fd1[1], writeFile, 1);
        }

        close(fd1[1]);
        close(ffd[0]);

        // waits on child to finish ----------------------------
        wait(NULL);


        return 0;
    }
}

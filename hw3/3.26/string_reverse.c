#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]){

    int fd1[2];
    int fd2[2];

    if(pipe(fd1) == -1){
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    if(pipe(fd2) == -1){
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    pid_t pid;
    pid = fork();
    
    if (pid < 0){ // Fork Failed
        perror("Fork failed");
    }
    else if(pid == 0){ // child process
        char newString[50];
        // closes the write end of the first pipe
        close(fd1[1]);

        /// child reads message from pipe
        read(fd1[0], newString, 50);

        // reverese the capitalization of the message
        for (int i = 0; newString[i] != '\0'; ++i){
            if(isupper(newString[i]) > 0){
                newString[i] = tolower(newString[i]);
            }
            else if(islower(newString[i]) > 0){
                newString[i] = toupper(newString[i]);
            }
        }

        // child sends the reversed message back through the pipe
        close(fd1[0]);
        close(fd2[0]);
        write(fd2[1], newString, 50);
        close(fd2[1]);

        return 0;
    }
    else{ // parent process
        char string[50];
        char revString[50];
        // close the read end of the first pipe
        close(fd1[0]);

        // takes in the message
        printf("%s", "Please type in a message: ");
        fgets(string, 50, stdin);

        // parent writes message into pipe
        write(fd1[1], string, 50);
        close(fd1[1]);

        // waits on child to return the new string
        wait(NULL);
        
        close(fd2[1]);

        // parent reads the reversed message from the pipe
        read(fd2[0], revString, 50);
        // parent prints reversed message
        printf("%s", revString);

        return 0;
    }
}
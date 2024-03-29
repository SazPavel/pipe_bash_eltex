#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    int status;
    pid_t pid, pid1;
    if(pipe(fd) == -1)
    {
        perror("pipe");
        exit(-1);
    }
    pid = fork();
    if(pid == -1)
    {
        perror("fork1");
        exit(-1);
    }
    if(pid == 0){
        dup2(fd[1], 1);
        close(fd[0]);
        execlp("ls", "", "-la", NULL);
        exit(0);
    }else{
        waitpid(pid, &status, 0);
        pid1 = fork();
        close(fd[1]);
        if(pid1 == -1)
        {
            perror("fork2");
            exit(-1);
        }
        if(pid1 == 0){
            dup2(fd[0], 0);
            execlp("wc", "", NULL);
        }else{
            wait(NULL);
            //sleep(2);
        }
    }
    exit(0);
}
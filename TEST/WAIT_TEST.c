#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

// ls | grep .c 
int main(void)
{
    int r, status;
    int pipefd[2];

    r = pipe(pipefd);
    char    *argv1[] = {"/bin/ls","./", NULL};
    char    *argv2[] = {"/usr/bin/grep",".c", NULL};
    char    *argv3[] = {"/usr/bin/wc", NULL};


    //ls
    pid_t child1 = fork();
    printf("child1 pid:%d\n",child1);
    if (child1 == 0) {
        sleep(20);
        printf("child1\n");
        exit(1);
    }

    //grep s
    pid_t child2 = fork();
    printf("child2 pid:%d\n",child2);
    if (child2 == 0) {
        sleep(5);
        printf("child2\n");
        exit(1);
    }

    pid_t child3 = fork();
    printf("child3 pid:%d\n",child3);
    if (child3 == 0) {
        sleep(10);
        printf("child3\n");
        exit(1);
    }

    // r = waitpid(child1, &status, 0);
    r = wait(&status);
    printf("FIRST:%d\n",r);
    r = wait(&status);
    printf("SECOND:%d\n",r);
    r = wait(&status);
    printf("THIRD:%d\n",r);
}
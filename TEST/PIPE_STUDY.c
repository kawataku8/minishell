#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

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
    if (child1 == 0) {
        close(pipefd[0]);
	printf("hello");
	fork();
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        execve(argv1[0], argv1, environ);
    }

    //grep s
    pid_t child2 = fork();
    if (child2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        execve(argv2[0], argv2, environ);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    // r = waitpid(child1, &status, 0);
    r = waitpid(child2, &status, 0);
}

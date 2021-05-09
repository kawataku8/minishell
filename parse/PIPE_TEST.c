#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
    int r, status;
    int pipefd[2];

    r = pipe(pipefd);

    pid_t child1 = fork();
    if (child1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        char    *argv[] = {"/bin/ls","./", NULL};
        execve(argv[0], argv, environ);
    }

    pid_t child2 = fork();
    if (child2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        char    *argv[] = {"/usr/bin/grep","txt", NULL};
        execve(argv[0], argv, environ);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    r = waitpid(child1, &status, 0);
    r = waitpid(child2, &status, 0);
}
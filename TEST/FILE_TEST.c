#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

extern char **environ;


// save original fds and reset them
int main(void)
{
    int fd;

    fd = open("./outtest1", O_CREAT | O_RDWR, S_IRWXU);

    int saved_std_out = dup(1);

    close(1);
    dup2(fd, 1);
    close(fd);

    int pid = fork();
    if (pid == 0)
    {
        char *argv[] = {"/bin/echo", "GOOD AFTERNOONNNNNN", NULL};
        execve(argv[0], argv, environ);
    }

    int status;
    wait(&status);

    // 1　に繋がっているファイルをcloseするので必須な気がする
    close(1);
    dup2(saved_std_out, 1);
    close(saved_std_out);
    char *str = "onigiri";
    write(1, str, strlen(str));

    return 0;
}
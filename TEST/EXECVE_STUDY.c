#include <unistd.h>

extern char **environ;

int main(void)
{
        // char *argv[3];

        // argv[0] = "/usr/bin/wc";
        // argv[1] = "./hello.txt";
        // argv[2] = NULL;

        char    *argv[] = {"/usr/bin/wc","./hello.txt", NULL};
        execve(argv[0], argv, environ);

        return 1;

        
}
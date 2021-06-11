#include <unistd.h>
#include <stdio.h>


extern char **environ;

int main(void)
{
        // char *argv[3];

        // argv[0] = "/usr/bin/wc";
        // argv[1] = "./hello.txt";
        // argv[2] = NULL;

        char    *argv[] = {"/bin/echo","./hello.txt", NULL};
        execve(argv[0], argv, environ);

        printf("YOYOY\n");

        return 1;

        
}
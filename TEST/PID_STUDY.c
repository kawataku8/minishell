#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>

int pipe_fd[2];

void do_child(void)
{
        // char *p = "Hello, dad or mam!\n";

        printf("This is child.\n");
}

void do_parent(void)
{
        // char c;
        int count, status;

        printf("This is parent.\n");

        // close(pipe_fd[1]);

        // while ((count = read(pipe_fd[0], &c, 1)) > 0) {
        //         putchar(c);
        // }

        // if (count < 0) {
        //         perror("read");
        //         exit(1);
        // }

        if (wait(&status) < 0) {
                perror("wait");
                exit(1);
        }
}

int main(void)
{
        int child,status;

        if ((child = fork()) == 0) {
                //child processでは走らせたものは必ずexitするので、その下のコードを実行することはない
                do_child();
                exit(1);
        }
        // do_parent();
        printf("this is dad \n");
        if (wait(&status) < 0) {
            printf("DEBUG:%d\n",status);
            perror("wait");
            exit(1);
        }
        printf("END\n");

        return 0;
}
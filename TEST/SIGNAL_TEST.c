#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


int main(void)
{
    // redirect out test
	int out_fd;
	out_fd = open("sigput", O_CREAT | O_RDWR, S_IRWXU);

    close(1);
    dup2(out_fd,1);
    close(out_fd);

    printf("SIG TEST OUT\n");


    return 0;
}
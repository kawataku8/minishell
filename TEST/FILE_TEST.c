#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
    int fd;

    fd = open("./outtest1", O_RDWR | O_CREAT);
    write(fd,"Y",1);

    close(fd);
    
    return 0;
}
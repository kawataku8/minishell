#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

extern char **environ;

int main(void)
{
	int fd;

	fd = open("fileTEST2.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);

	// printf("fd:%d\n",fd);
	char *s = "This is testing O_TRUNC mode of open\n";
	char *s1 = "YOYOYO\n";
	write(fd, s1, strlen(s1));
	
	close(fd);

	return 0;
}
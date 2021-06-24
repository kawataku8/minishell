#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	int file_fd;
	file_fd = open("output", O_CREAT | O_RDWR, S_IRWXU);

	// close(1);
	dup2(file_fd, 1);
	// close(file_fd);

	char *s = "hello\n";
	write(1, s, strlen(s));
	return 2;
}
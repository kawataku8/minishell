#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	char *s = "MORNING\n";
	// char *str = "YOYOYO\n";
	// write(5, s, strlen(s));
	// write(1, str, strlen(str));

	int file_fd = open("ftout", O_CREAT | O_RDWR, S_IRWXU);
		
	close(5);
	dup2(file_fd, 5);
	close(file_fd);

	
	write(5, s, strlen(s));


	return 0;
}
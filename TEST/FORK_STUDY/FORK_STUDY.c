#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

extern char **environ;
int main(void)

{
	int r, status,file_fd;
	char *s = "YOYOYO\n";
	

	file_fd = open("out202", O_CREAT | O_RDWR, S_IRWXU);
	close(2);
	dup2(file_fd,2);
	close(file_fd);
	
	pid_t child1 = fork();
	printf("PARENT:child1 pid:%d\n", child1);
	if (child1 == 0)
	{
		write(file_fd, s, strlen(s));
	}

	printf("========\n");
	r = wait(&status);
	printf("FIRST:%d\n", r);

	return 0;
}
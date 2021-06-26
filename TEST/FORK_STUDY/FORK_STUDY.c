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

	pid_t child1 = fork();
	if (child1 == 0)
	{
		printf("THIS IS CHILD1\n");
	}

	pid_t child2 = fork();
	if (child2 == 0)
	{
		printf("THIS IS CHILD2\n");
	}

	pid_t child3 = fork();
	if (child3 == 0)
	{
		printf("THIS IS CHILD3\n");
	}

	printf("==================\n");
	while((r = wait(&status)) != -1)
	{
		printf("STATUS:%d\n",r);
	}

	return 0;
}
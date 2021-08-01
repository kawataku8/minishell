#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

extern char **environ;

int main(void)
{
	int status, r;


	pid_t child = fork();
	if(child == 0)
	{
		char *argv[] = {"/usr/bin/export", NULL};
		execve(argv[0], argv, environ);
		if (execve(argv[0], argv, environ) == -1)
			printf("MISSION FAIL\n");
		exit(1);
	}

	r = wait(&status);
	printf("%d,%d\n",r,status);

	return 1;
}
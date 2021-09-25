#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

extern char **environ;

int main(void)
{
	char *pass = "/Users/takuya/Documents/42Tokyo/myProjects/minishell/TEST/exec_test/hello.out";
	char *argv[] = {pass,NULL};
	if (execve(argv[0], argv, environ) == -1)
	{
		printf("FAILED\n");
	}
	return 0;
}
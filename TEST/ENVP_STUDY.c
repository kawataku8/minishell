 
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

extern char **environ;

int main(void)
{
	int status;
	int pid;

	pid = fork();
	if (pid == 0)
	{
		char *argv[] = {"/bin/ls", "./", NULL};
		char **tmp_env_list = make_char_env_list()
		execve(argv[0], argv,environ);
		exit(1);
	}
	wait(&status);

	// while(*environ != NULL)
	// {
	// 	printf("%s\n",*environ);
	// 	environ++;
	// }
	
	return 0;
}
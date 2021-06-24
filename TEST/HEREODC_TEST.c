#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

extern char **environ;

int main(void)
{
	char *s = "HELLO WORLD";
	char *usr_input;

	// close(0);
	write(0,s,strlen(s));

	char *argv[] = {"/bin/cat", NULL};
	execve(argv[0],argv,environ);

	return 0;
}
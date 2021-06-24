#include <unistd.h>
#include <stdio.h>


extern char **environ;

int main(void)
{
	
	fh
	char *argv[] = {"/bin/echo", "./hello.txt", NULL};
	execve(argv[0], argv, environ);

	printf("YOYOY\n");

	return 1;
}
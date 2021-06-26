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
	// char *s = "HELLO WORLD";
	// char *usr_input;

	// write(0,s,strlen(s));

	// int file_fd = open("hello.txt", O_CREAT | O_RDWR, S_IRWXU);
	// close(0);
	// dup2(file_fd,0);
	// close(file_fd);


	// usr_input = readline("INPUT: ");
	// printf("DEBUG:%s\n",usr_input);

	// char *argv[] = {"/bin/cat", NULL};
	// execve(argv[0],argv,environ);

	unlink("./hello.txt");

	return 0;
}
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

int num(void)
{
	return 123;
}

int main(void)
{
	// char *s = "$USER";
	// char *argv[] = {"/bin/echo", s, NULL};
	// execve(argv[0], argv, environ);

	// pid_t child1 = fork();
	// if(child1 == 0)
	// {
	// 	char *argv[] = {"/bin/echo", "YOHELLO", NULL};
	// 	execve(argv[0], argv, environ);
	// 	printf("hello\n");
	// }
	// int status;
	// int r = wait(&status);
	// printf("r:%d, status:%d\n",r,status);

	// printf("errno is :%d\n",errno);
	
	// char *str = strdup("ABC");
	// free(str);
	// str = NULL;
	// printf("%c\n",str[1]);

	int file_fd = open("nofile", O_RDWR);
	printf("errno:%d\n",errno);
	close(file_fd);
	return 0;
}
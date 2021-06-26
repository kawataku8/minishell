#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void sigint_handler(int signum)
{
	printf("11111\n");
}

void sigint_handler2(int signum)
{
	printf("222222\n");
}

void sigquit_handler(int signum)
{
	printf("SIGQUIT\n");
}

int main(void)
{
	signal(SIGINT, &sigint_handler);
	// / signal(SIGQUIT, SIG_IGN);
	

	for(int i = 0; i < 10; i++)
	{
		printf("1-%d\n",i);
		sleep(1);
		i++;
	}
	
	signal(SIGINT, &sigint_handler2);

	for(int i = 0; i < 10; i++)
	{
		printf("2-%d\n",i);
		sleep(1);
		i++;
	}

	signal(SIGINT, &sigint_handler);
	for (int i = 0; i < 10; i++)
	{
		printf("3-%d\n",i);
		sleep(1);
		i++;
	}

	exit(1);
	return 0;
}

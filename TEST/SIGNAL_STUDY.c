#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t sigint_count = 3;

void sigint_handler(int signum)
{
	printf("sigint_handler\n");

	// if (--sigint_count <= 0)
	// {
	// 	printf("sigint_handler: exiting ...\n");
	// 	exit(1);
	// }
}

void sigquit_handler(int signum)
{
	printf("QUITHANDLER\n");
	// if (--sigint_count <= 0)
	// {
	// 	printf("sigint_handler: exiting ...\n");
	// 	exit(1);
	// }
}


int main(void)
{
	char *usr_input;
	int size = 100;

	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, &sigquit_handler);

	for (int i = 0; i < 10; i++)
	{
		printf("[%d]\n",i);
		sleep(1);
	}
	
	
	return 0;
}
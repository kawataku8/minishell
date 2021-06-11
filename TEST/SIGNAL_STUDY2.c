
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t sigint_count = 3;

void sigint_handler(int signum)
{
	printf("INTRHANDLER\n");

	// if (--sigint_count <= 0)
	// {
	// 	printf("sigint_handler: exiting ...\n");
	// 	exit(1);
	// }
	exit(1);
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

void do_child(void)
{
	printf("IN CHILD PS\n");
	for (int i = 0; i < 5; i++)
	{
		printf("[%d]\n",i);
		sleep(1);
	}
	exit(1);
} 


int main(void)
{
	char *usr_input;
	int size = 100;

	// usr_input = (char*)malloc(sizeof(char)*size);
	// signal(SIGINT, &sigint_handler);
	// signal(SIGQUIT, &sigquit_handler);
	
	int pid;
	pid = fork();
	if (pid ==0)
	{
		printf("CHILD\n");
		do_child();
		exit(1);
	}
	

	int status;
	int r = wait(&status);
	printf("PARENT,r:[%d]\n",r);

	// for (;;)
	// {
	// 	printf("main: sigint_count(%d), calling pause ...\n",
	// 		sigint_count);

	// 	pause();

	// 	printf("main: returned from pause. sigint_count(%d)\n",
	// 		sigint_count);
	// }

	return 0;
}

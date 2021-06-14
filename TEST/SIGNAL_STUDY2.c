
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t sigint_count = 3;

void sigint_handler(int signum)
{
	printf("INTRHANDLER\n");
}

void sigquit_handler(int signum)
{
	printf("QUITHANDLER\n");
	exit(1);
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
	// signal(SIGINT, &sigint_handler);
	// signal(SIGQUIT, &sigquit_handler);
	
	int pid;
	pid = fork();
	if (pid ==0)
	{
		do_child();
	}
	

	int status;
	int r = wait(&status);
	printf("PARENT,r:[%d]\n",r);


	return 0;
}

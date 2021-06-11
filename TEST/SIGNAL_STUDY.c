#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t sigint_count = 3;

void sigint_handler(int signum)
{
	printf("sigint_handler: signum(%d), sigint_count(%d)\n",
		   signum, sigint_count);

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

	// usr_input = (char*)malloc(sizeof(char)*size);
	// signal(SIGINT, &sigint_handler);
	// signal(SIGQUIT, &sigquit_handler);
	
	// int pid;
	// pid = fork();
	// if (pid ==0)
	// {
	// 	printf("CHILD\n");
	// 	pause();
	// 	exit(1);
	// }
	
	printf("FIRST PAUSE\n");
	// fgets(usr_input, size, stdin);

	for (int i = 0; i < 10; i++)
	{
		printf("[%d]\n",i);
		sleep(1);
	}
	


	// int status;
	// int r = wait(&status);

	// printf("PARENT,input:[%s]\n",usr_input);

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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t sigint_count = 3;

void sigint_handler(int signum)
{
	printf("sigint_handler: signum(%d), sigint_count(%d)\n",
		   signum, sigint_count);

	if (--sigint_count <= 0)
	{
		printf("sigint_handler: exiting ...\n");
		exit(1);
	}

}

int main(void)
{
	
	signal(SIGINT, &sigint_handler);

	for (;;)
	{
		printf("main: sigint_count(%d), calling pause ...\n",
			sigint_count);

		pause();

		printf("main: returned from pause. sigint_count(%d)\n",
			sigint_count);
	}

	return 0;
}
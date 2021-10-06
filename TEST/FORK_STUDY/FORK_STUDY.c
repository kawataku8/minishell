#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

extern char **environ;
volatile sig_atomic_t g_signal_handled = 0;

void sigint_handler(int signum)
{
	if (g_signal_handled == 0)
	{
		printf("INPUT HANDLE 22 \n");
		g_signal_handled = 1;
		return ;
	}
	printf("SIG HANDLER 11\n");
	// exit(3);
}

/* readline()内から定期的に呼ばれる関数 */
static int check_state()
{
	if (g_signal_handled)
	{
		// g_signal_handled = 0;

		/* 入力中のテキストを破棄 */
		rl_delete_text(0, rl_end);

		/* readline()をreturnさせる */
		rl_done = 1;
	}
	return 0;
}

int main(void)
{
	char *user_input = NULL;
	int r, status,file_fd;
	pid_t child1 = fork();

	signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, sigint_handler);

	if (child1 == 0)
	{
		rl_event_hook = check_state;
		printf("IN CHILD PROCESS\n");
		char *line = NULL;
		// while (1)
		while ((line = readline("> ")) != NULL)
		{
			// line = readline("> ");
			if (g_signal_handled)
			{
				printf("YOYOYO\n");
				exit(g_signal_handled);
			}
			printf("line is [%s]\n", line);
			free(line);
		}
		printf("AFTER LOOP\n");
		exit(2);
	}

	// r = waitpid(child1, &status, 0);
	// r = wait(&status);
	// if (WIFSIGNALED(status))
	// {
	// 	printf("SIGNAL CAUGHT!!!\n");
	// 	printf("CHILD PROCESS STOPPED by SIGNAL[%d]\n", WTERMSIG(status));
	// }
	// // printf("%d:%d\n", r, stats);
	// printf("EXIT status is [%d]\n", WEXITSTATUS(status));

	while ((r = wait(&status)) != -1)
	{
		if (WIFSIGNALED(status))
			printf("CHILD PROCESS STOPPED by SIGNAL [%d]\n",WTERMSIG(status));
		if (WIFSTOPPED(status))
		{
			printf("SIGNAL is [%d]\n", WSTOPSIG(status));
		}
		printf("%d:%d\n", r, status);
		printf("EXIT status is [%d]\n", WEXITSTATUS(status));
	}

	return 0;
}



// void ch_procs(void)
// {
// 	pid_t child1 = fork();

// 	if (child1 == 0)
// 	{
// 		printf("IM CHILD \n");
// 		exit(2);
// 	}
// 	printf("pid is [%d]\n",child1);
// 	printf("IM PARENT!!\n");
// }

// int main(void)
// {
// 	int r, status, file_fd;

// 	printf("=====11111111=====\n");
// 	ch_procs();
// 	printf("=====22222222=====\n");

// 	while ((r = wait(&status)) != -1)
// 	{
// 		printf("%d:%d\n", r, status);
// 		printf("EXIT status is [%d]\n", WEXITSTATUS(status));
// 	}
// 	return (0);
// }
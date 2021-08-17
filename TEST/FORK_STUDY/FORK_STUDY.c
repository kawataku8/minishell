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
volatile sig_atomic_t signal_handled = 0;

void sigint_handler(int signum)
{
	// printf("SIGNAL\n");
	// exit_status = 5;
	signal_handled = 1;
	// exit(3);
}

/* readline()内から定期的に呼ばれる関数 */
static int check_state()
{
	if (signal_handled)
	{
		// signal_handled = 0;

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
	// pid_t child1 = fork();

	signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, sigint_handler);

	rl_event_hook = check_state;

	char *line = NULL;
	while (1)
	{
		line = readline("> ");
		if (signal_handled == 1)
		{
			break;
		}
		printf("line is [%s]\n", line);
		free(line);
	}
	printf("\nexit\n");

	// if (child1 == 0)
	// {
	// 	// char *argv[] = {"/bin/sleep", "5",NULL};
	// 	// if (execve(argv[0], argv, environ) == -1)
	// 	// 	printf("MISSION FAIL\n");
	// 	user_input = readline("INPUT:");
	// 	printf("555:%s\n",user_input);
	// 	exit(2);
	// }

	// r = waitpid(child1, &status, 0);
	// r = wait(&status);
	// if (WIFSIGNALED(status))
	// {
	// 	printf("SIGNAL CAUGHT!!!\n");
	// 	printf("CHILD PROCESS STOPPED by SIGNAL[%d]\n", WTERMSIG(status));
	// }
	// // printf("%d:%d\n", r, stats);
	// printf("EXIT status is [%d]\n", WEXITSTATUS(status));

	// while ((r = wait(&status)) != -1)
	// {
	// 	if (user_input != NULL)
	// 		free(user_input);
	// 	if (WIFSIGNALED(status))
	// 		printf("CHILD PROCESS STOPPED by SIGNAL [%d]\n",WTERMSIG(status));
	// 	if (WIFSTOPPED(status))
	// 	{
	// 		printf("SIGNAL is [%d]\n", WSTOPSIG(status));
	// 	}
	// 	printf("%d:%d\n", r, status);
	// 	printf("EXIT status is [%d]\n", WEXITSTATUS(status));
	// }

	return 0;
}
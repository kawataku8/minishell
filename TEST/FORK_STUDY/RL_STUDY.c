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
		g_signal_handled = 1;
		return ;
	}	
}

void sigquit_handler(int signum)
{
	printf("SIG QUIT\n");
	exit(1);
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

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);

	rl_event_hook = check_state;
	char *line = NULL;
	while((line = readline("> ")) != NULL)
	{
		if(g_signal_handled)
		{
			g_signal_handled = 0;
			continue ;
		}
		// line = readline("> ");
		if (line == NULL)
		{
			printf("Ctrl + D is pressed!!\n");
			exit(1);
		}
		printf("line is [%s]\n", line);
		free(line);
	}
	printf("AFTER LOOP\n");

	return 0;
}


#include "../../include/signal.h"

void sigint_handler(int signum)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void sigquit_handler(int signum)
{
	// TODO: readline中かコマンド実行中かによって
	// sigquit条件分岐 -> GLOBAL変数でg_is_readline 必要？？
	printf("SIGQUIT\n");
}

void setup_signals(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

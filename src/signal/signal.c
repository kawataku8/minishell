#include "../../include/signal.h"

extern volatile sig_atomic_t signal_handled;

void sigint_handler(int signum)
{
	// printf("DEBUG:sigint\n");
	if (signal_handled == 0)
	{
		signal_handled = 1;
		return ;
	}
	// else if (signal_handled == 2)
	// {
	// 	// 処理
	// 	return ;
	// }
}

void sigquit_handler(int signum)
{
	// TODO: readline中かコマンド実行中かによって
	// sigquit条件分岐 -> GLOBAL変数でg_is_readline 必要？？
	return ;
}

void setup_signals(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

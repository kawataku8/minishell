#include "../../include/signal.h"

extern volatile sig_atomic_t signal_handled;

int check_state(void)
{
	if (signal_handled)
	{
		signal_handled = 0;

		/* 入力中のテキストを破棄 */
		rl_delete_text(0, rl_end);

		/* readline()をreturnさせる */
		rl_done = 1;
	}
	return 0;
}
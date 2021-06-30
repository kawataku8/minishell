#include "../../include/parse.h"

void save_orig_fd(int *orig_stdin, int *orig_stdout, int *orig_stderr)
{
	*orig_stdin = dup(0);
	*orig_stdout = dup(1);
	*orig_stderr = dup(2);
}

void reset_fds_orig(int orig_stdin, int orig_stdout, int orig_stderr)
{
	close(0);
	dup2(orig_stdin, 0);
	close(orig_stdin);
	close(1);
	dup2(orig_stdout, 1);
	close(orig_stdout);
	close(2);
	dup2(orig_stderr, 2);
	close(orig_stderr);
}

void close_red_filefds(t_list *token_list)
{
	t_list *cur_list;
	t_token *token;

	cur_list = token_list;
	while (cur_list != NULL)
	{
		token = ((t_token*)cur_list->content);
		if (token->type == REDFD)
			close(ft_atoi(token->word));
		cur_list = cur_list->next;
	}
}
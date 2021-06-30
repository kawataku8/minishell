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
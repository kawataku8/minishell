#include "../../include/parse.h"

void save_orig_fd(int *orig_stdin, int *orig_stdout, int *orig_stderr)
{
	*orig_stdin = dup(0);
	*orig_stdout = dup(1);
	*orig_stderr = dup(2);
}
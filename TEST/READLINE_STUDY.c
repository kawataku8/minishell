#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char *line;

	while ((line = readline(">> ")) != NULL)
	{
		if (strlen(line) > 0)
		{
			add_history(line);
		}

		printf("[%s]\n", line);

		// readline malloc's a new buffer every time.
		free(line);
		rl_on_new_line();
	}
	return (0);
}
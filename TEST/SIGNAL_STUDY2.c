#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void sigint_handler(int signum)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void sigquit_handler(int signum)
{
	printf("SIGQUIT\n");
}

int main(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
		
	char *usr_input;

	printf("THIS IS DEBUG\n");
	
	while((usr_input = readline("minishell$ ")) != NULL)
	{
		printf("%s\n",usr_input);
		free(usr_input);
		usr_input = NULL;
	}

	exit(1);
	return 0;
}

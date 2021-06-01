#include "../include/commonlib.h"
#include "../include/parse.h"
#include "../include/validator.h"
#include "../include/cmd.h"
#include "../include/env_operations.h"

int main(int argc, char *argv[], char **envp)
{
	t_doubly_list *env_list;
	char *value;

	env_list = make_envlist(envp);

	value = get_value_from_envlist("HEME",env_list);

	if (value != NULL)
	{
		printf("%s\n",value);
		free(value);
	}
	
	exit(0);
	return 0;
}
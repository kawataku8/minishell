
#include "../include/commonlib.h"
#include "../include/parse.h"
#include "../include/validator.h"
#include "../include/cmd.h"
#include "../include/env_operations.h"


t_list *null_test(t_list *token_list)
{
	t_list *cur_node = token_list;
	t_list *end_node = cur_node;
	t_list *res_node;
	int i = 0;

	while(end_node != NULL)
	{
		if(i == 3)
		{
			res_node = end_node->next;
			end_node->next = NULL;
			break;
		}
		i++;
		end_node = end_node->next;
	}
	return (res_node);
}

int main(int argc, char *argv[], char **envp)
{
	char *usr_input;
	int size = 100;
	t_list *token_list;
	t_doubly_list *env_list;


	usr_input = (char*)malloc(sizeof(char)*size);
	fgets(usr_input,size,stdin);

	usr_input[ft_strlen(usr_input)-1] = '\0';
	printf("USER INPUT:%s\n",usr_input);
	
	token_list = make_tokenlist(usr_input);
	print_tokenlist(token_list);

	if(validator(token_list) == 0)
		printf("INVALID\n");
	else
		printf("GOOD\n");

	t_list *cmd_list;
	cmd_list = split_tokens(token_list);
	print_cmdlist(cmd_list);

	printf("-------------------\n");
	env_list = make_envlist(envp);
	edit_env(cmd_list, env_list);
	print_cmdlist(cmd_list);
	//whileでcmdlist回して、それぞれのコマンド実行
	// process_cmdlist(cmd_list);

	free(usr_input);
	exit(1);
	return 0;
}

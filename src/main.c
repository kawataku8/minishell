#include "../include/commonlib.h"
#include "../include/parse.h"
#include "../include/validator.h"
#include "../include/cmd.h"
#include "../include/env_operations.h"
#include "../include/setup.h"
#include "../include/main.h"
#include "../include/signal.h"


void print_cmdlist_withmeta(t_list *cmd_list)
{
	t_list *cur_node = cmd_list;
	t_cmd_node *cur_cmd;

	while(cur_node != NULL)
	{
		cur_cmd = ((t_cmd_node*)cur_node->content);
		printf("pid:[%d]\n",cur_cmd->pid);
		printf("op:[%d]\n",cur_cmd->op);
		printf("argc:[%d]\n",cur_cmd->argc);
		printf("---------------------------\n");
		cur_node = cur_node->next;
	}
}

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

void del_token(void *content)
{
	free(((t_token*)content)->word);
	free((t_token*)content);
}

void free_cmdlist(t_list **cmd_list)
{
	t_list *cur_cmdlist;
	t_list *next_cmdlist;

	cur_cmdlist = *cmd_list;
	while (cur_cmdlist != NULL)
	{
		next_cmdlist = cur_cmdlist->next;
		// if (((t_cmd_node*)cur_cmdlist->content)->red_in_filepath != NULL)
		// 	free(((t_cmd_node *)cur_cmdlist->content)->red_in_filepath);
		// if (((t_cmd_node*)cur_cmdlist->content)->red_out_filepath != NULL)
		// 	free(((t_cmd_node *)cur_cmdlist->content)->red_out_filepath);
		// if (((t_cmd_node*)cur_cmdlist->content)->red_err_filepath != NULL)
		// 	free(((t_cmd_node *)cur_cmdlist->content)->red_err_filepath);
		// free_splitstr(((t_cmd_node*)cur_cmdlist->content)->argv);
		ft_lstclear(&((t_cmd_node*)cur_cmdlist->content)->token_list, &del_token);
		cur_cmdlist = next_cmdlist;
	}

}

int main(int argc, char *argv[], char **envp)
{
	char *usr_input;
	char *tmp;
	t_list *token_list;
	t_env_list *env_list;

	setup_signals();

	env_list = make_envlist(envp);
	while ((usr_input = readline("minishell$ ")) != NULL)
	{
		if (ft_strlen(usr_input) > 0)
			add_history(usr_input);
		else
			continue ;

		tmp = ft_strtrim(usr_input,"	 ");
		free(usr_input);
		usr_input = tmp;
			
		token_list = make_tokenlist(usr_input);
		
		if (validator(token_list) == 0)
		{
			printf("INVALID\n");
			free(usr_input);
			usr_input = NULL;
			continue ;
		}
		else
			printf("GOOD\n");

		//token_listからcmd_list生成
		t_list *cmd_list;
		cmd_list = make_cmdlist(token_list);
		print_cmdlist(cmd_list);

		setup_op(cmd_list);

		process_cmdlist(cmd_list, env_list);

		free(usr_input);
		usr_input = NULL;
		free_cmdlist(&cmd_list);
	}
	
	exit(1);
	return 0;
}

#include "../../include/parse.h"
#include "../../include/validator.h"

void print_cmdlist(t_list *cmd_list)
{
	t_list *cur_node = cmd_list;
	t_list *cur_token;

	while(cur_node != NULL)
	{
		cur_token = ((t_cmd_node*)cur_node->content)->token_list;
		while (cur_token != NULL)
		{
			printf("[%s] ",((t_token*)cur_token->content)->word);
			cur_token = cur_token->next;
		}
		printf("\n");
		cur_node = cur_node->next;
	}
}

t_list *split_tokens(t_list *token_list)
{
	t_list *cmd_list;
	t_cmd_node *cmd_node;
	t_list *i_token;
	t_list *j_token;
	t_list *next_i;

	cmd_list = NULL;
	i_token = token_list;
	while(i_token != NULL)
	{
		j_token = i_token;
		while (j_token != NULL)
		{
			if (((t_token*)j_token->content)->type == SCOLON
			|| ((t_token*)j_token->content)->type == PIPE)
				break ;
			j_token = j_token->next;
		}
		if(j_token == NULL)
			next_i = NULL;
		else
		{
			next_i = j_token->next;
			j_token->next = NULL;
		}
		// make_cmdnode();
		cmd_node = (t_cmd_node*)malloc(sizeof(t_cmd_node));
		cmd_node->token_list = i_token;
		ft_lstadd_back(&cmd_list,ft_lstnew((void*)cmd_node));
		i_token = next_i;
	}
	return (cmd_list);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 20:36:01 by takuya            #+#    #+#             */
/*   Updated: 2021/09/19 21:08:48 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/setup.h"

int	count_STR(t_list *token)
{
	int		counter;
	t_list	*cur_token;

	counter = 0;
	cur_token = token;
	while (cur_token != NULL)
	{
		if (((t_token *)cur_token->content)->type == STR)
			++counter;
		cur_token = cur_token->next;
	}
	return (counter);
}

// TODO: ft_studup()でnew_argvに入れるべき？
void	setup_argv_argc(t_cmd_node *cmd_node)
{
	int	new_argc;
	int	i;
	t_list	*cur_token;
	char	**new_argv;

	cur_token = cmd_node->token_list;
	new_argc = count_STR(cur_token);
	new_argv = (char **)malloc(sizeof(char *) * new_argc + 1);
	i = 0;
	while (cur_token != NULL)
	{
		if (((t_token *)cur_token->content)->type == STR)
			new_argv[i++] = ((t_token *)cur_token->content)->word;
		cur_token = cur_token->next;
	}
	new_argv[i] = NULL;
	cmd_node->argc = new_argc;
	cmd_node->argv = new_argv;
}

void	setup_op(t_list *cmd_list)
{
	t_list	*cur_cmd;
	t_list	*cur_token;

	cur_cmd = cmd_list;
	while (cur_cmd != NULL)
	{
		((t_cmd_node *)cur_cmd->content)->op = SCOLON;
		cur_token = ((t_cmd_node *)cur_cmd->content)->token_list;
		while (cur_token != NULL)
		{
			if (((t_token *)cur_token->content)->type == PIPE)
			{
				((t_cmd_node *)cur_cmd->content)->op = PIPE;
				break ;
			}
			cur_token = cur_token->next;
		}
		cur_cmd = cur_cmd->next;
	}
}

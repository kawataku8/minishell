/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 20:36:01 by takuya            #+#    #+#             */
/*   Updated: 2021/10/25 23:03:45 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/setup.h"

int	count_strtoken(t_list *token)
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

int	is_next_delim_space(t_list *cur_token)
{
	t_list	*token;
	int		flag;

	flag = 1;
	token = cur_token;
	while (token != NULL && ((t_token *)token->content)->type != MYSPACE)
	{
		if (((t_token *)token->content)->type == DQUOTE
			|| ((t_token *)token->content)->type == SQUOTE)
		{
			flag = 0;
			break ;
		}
		token = token->next;
	}
	return (flag);
}

char	*join_str_series(t_list **cur_token)
{
	t_list	*iter_token;
	char	*joined_str;
	char	*tmp;

	iter_token = (*cur_token)->next;
	joined_str = ft_strdup(((t_token *)(*cur_token)->content)->word);
	if (is_next_delim_space(*cur_token) == 1)
		return (joined_str);
	while (iter_token != NULL && (((t_token *)iter_token->content)->type == STR
			|| ((t_token *)iter_token->content)->type == DQUOTE
			|| ((t_token *)iter_token->content)->type == SQUOTE))
	{
		if (((t_token *)iter_token->content)->type == STR)
		{
			tmp = joined_str;
			joined_str = ft_strjoin(joined_str,
					((t_token *)iter_token->content)->word);
			free(tmp);
		}
		iter_token = iter_token->next;
	}
	*cur_token = iter_token;
	return (joined_str);
}

void	setup_argv_argc(t_cmd_node *cmd_node)
{
	int		new_argc;
	int		i;
	t_list	*cur_token;
	char	**new_argv;

	cur_token = cmd_node->token_list;
	new_argc = count_strtoken(cur_token);
	new_argv = (char **)malloc(sizeof(char *) * new_argc + 1);
	i = 0;
	while (cur_token != NULL)
	{
		if (((t_token *)cur_token->content)->type == STR)
			new_argv[i++] = join_str_series(&cur_token);
		if (cur_token == NULL)
			break ;
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

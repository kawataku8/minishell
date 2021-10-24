/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:35:45 by takuya            #+#    #+#             */
/*   Updated: 2021/10/24 21:09:07 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/validator.h"
#include "../../include/main.h"
#include "../../include/cmd.h"

t_list	*get_red_filepath_token(t_list *cur_token)
{
	while (cur_token != NULL)
	{
		if (((t_token *)cur_token->content)->type == STR)
		{
			((t_token *)cur_token->content)->type = REDFILEPATH;
			break ;
		}
		cur_token = cur_token->next;
	}
	return (cur_token);
}

//input	:
//output:good returns 1, open error returns 0
//description: 
// TODO:if line52 true, returns to main readline
int	connect_redirect(int red_type, int red_fd, char *red_filepath)
{
	int	file_fd;

	file_fd = -1;
	if (red_type == RDIR)
		file_fd = open(red_filepath, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	else if (red_type == RRDIR)
		file_fd = open(red_filepath, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	else if (red_type == LDIR || red_type == LLDIR)
		file_fd = open(red_filepath, O_RDWR, S_IRWXU);
	if (file_fd == -1)
	{
		my_write_err_msg(2, "minishell: ", errno);
		exit(1);
		return (0);
	}
	close(red_fd);
	dup2(file_fd, red_fd);
	close(file_fd);
	return (1);
}

int	set_red_fd(t_list *last_token, int red_type)
{
	if (last_token != NULL && ((t_token *)last_token->content)->type == REDFD)
		return (ft_atoi(((t_token *)last_token->content)->word));
	else
	{
		if (red_type == RDIR || red_type == RRDIR)
			return (1);
		else
			return (0);
	}
}

char	*set_red_filepath(int red_type, t_cmd_node *cmd_node,
t_list **cur_token)
{
	if (red_type == LLDIR)
		return (cmd_node->heredoc_filepath);
	else
	{
		*cur_token = get_red_filepath_token(*cur_token);
		return (((t_token *)(*cur_token)->content)->word);
	}
}

void	parse_redirect(t_cmd_node *cmd_node)
{
	t_list	*cur_token;
	t_list	*last_token;
	int		red_fd;
	int		red_type;
	char	*red_filepath;

	last_token = NULL;
	cur_token = cmd_node->token_list;
	while (cur_token != NULL)
	{
		red_type = is_red_token(((t_token *)cur_token->content));
		if (red_type != 0)
		{
			red_fd = set_red_fd(last_token, red_type);
			red_filepath = set_red_filepath(red_type, cmd_node, &cur_token);
			connect_redirect(red_type, red_fd, red_filepath);
		}
		last_token = cur_token;
		cur_token = cur_token->next;
	}
}

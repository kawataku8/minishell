/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:04:15 by takuya            #+#    #+#             */
/*   Updated: 2021/10/13 23:42:03 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/cmd.h"

extern volatile sig_atomic_t	g_signal_handled;

t_list	*get_heredoc_delim_token(t_list *cur_token)
{
	while (cur_token != NULL)
	{
		if (((t_token *)cur_token->content)->type == STR)
		{
			((t_token *)cur_token->content)->type = HEREDOC_DELIM;
			break ;
		}
		cur_token = cur_token->next;
	}
	return (cur_token);
}

int	open_heredoc_tmp(char *file_path)
{
	int		file_fd;

	file_fd = open(file_path, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	return (file_fd);
}

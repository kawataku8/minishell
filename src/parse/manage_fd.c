/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 22:10:44 by takuya            #+#    #+#             */
/*   Updated: 2021/10/25 20:53:02 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/main.h"

int	*dup_original_fds(void)
{
	int	*original_fds;

	original_fds = (int *)malloc(sizeof(int) * 3);
	if (original_fds == NULL)
	{
		my_write_err_msg(2, "minishell: mallco error \n", 0);
		exit(1);
	}
	original_fds[0] = dup(0);
	original_fds[1] = dup(1);
	original_fds[2] = dup(2);
	return (original_fds);
}

void	reset_fds_orig(int *original_fds)
{
	close(0);
	dup2(original_fds[0], 0);
	close(original_fds[0]);
	close(1);
	dup2(original_fds[1], 1);
	close(original_fds[1]);
	close(2);
	dup2(original_fds[2], 2);
	close(original_fds[2]);
	free(original_fds);
}

void	close_red_filefds(t_list *token_list)
{
	t_list	*cur_list;
	t_token	*token;

	cur_list = token_list;
	while (cur_list != NULL)
	{
		token = ((t_token *)cur_list->content);
		if (token->type == REDFD)
			close(ft_atoi(token->word));
		cur_list = cur_list->next;
	}
}

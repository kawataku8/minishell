/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmds_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:33:25 by takuya            #+#    #+#             */
/*   Updated: 2021/10/10 10:38:01 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cmd.h"
#include "../../include/parse.h"
#include "../../include/env_operations.h"

int	ispipe(t_cmd_node *cur_cmd_node)
{
	if (cur_cmd_node->op == PIPE)
		return (1);
	return (0);
}

void	del_cmdnode(void *content)
{
	int	i;

	i = 0;
	while (((t_cmd_node *)content)->argv[i] != NULL)
	{
		free(((t_cmd_node *)content)->argv[i]);
		i++;
	}
	free((t_cmd_node *)content);
}

void	dup_lastpipe(int haspipe, int *lastpipe)
{
	if (haspipe)
	{
		close(lastpipe[1]);
		dup2(lastpipe[0], 0);
		close(lastpipe[0]);
	}
}

void	dup_newpipe(t_cmd_node *cmd_node, int *newpipe)
{
	if (ispipe(cmd_node))
	{
		close(newpipe[0]);
		dup2(newpipe[1], 1);
		close(newpipe[1]);
	}
}

void	close_pipe(t_cmd_node *cmd_node, int haspipe,
int *lastpipe, int *newpipe)
{
	if (haspipe)
	{
		close(lastpipe[0]);
		close(lastpipe[1]);
	}
	if (ispipe(cmd_node))
	{
		lastpipe[0] = newpipe[0];
		lastpipe[1] = newpipe[1];
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:08:16 by takuya            #+#    #+#             */
/*   Updated: 2021/10/02 13:10:16 by takuya           ###   ########.fr       */
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

// returns each command's pid
pid_t	start_command(t_cmd_node *cmd_node, t_env_list *env_list, int haspipe, int *lastpipe)
{
	pid_t	pid;
	int		newpipe[2];
	int		exit_status;
	char	**dchar_envlist;

	if (ispipe(cmd_node))
		pipe(newpipe);
	pid = fork();
	if (pid == 0)
	{
		dup_lastpipe(haspipe, lastpipe);
		dup_newpipe(cmd_node, newpipe);
		
	 	parse_redirect(cmd_node);

		if (get_ft_buildin_idx(cmd_node->argv) > -1)
		{
			exit_status = execute_buildin(cmd_node, env_list, 2);
			exit(exit_status);
		}
		else
		{
			find_abscmd_path(cmd_node->argv);
			dchar_envlist = make_char_envlist(env_list);
			// TODO; if execve fails, returns -1. Check errno and Do error handle
			if (execve(cmd_node->argv[0], cmd_node->argv, dchar_envlist) == -1)
			{
				// TODO: check errno
				// code for fail execve()
				printf("minishell: command not found\n");
				exit(127);
			}
		}
	}
	
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
	return (pid);
}

int	*set_up_pipe(void)
{
	int	*new_pipe;

	new_pipe = (int *)malloc(sizeof(int) * 2);
	if (new_pipe == NULL)
	{
		printf("ERROR: mallloc error\n");
		exit(1);
	}
	new_pipe[0] = -1;
	new_pipe[1] = -1;
	return (new_pipe);
}

// piple list の実行されたものの中で最後(右端)のコマンドのポインタを返す
t_list	*exec_multi_cmds(t_list *cmd_list, t_env_list *env_list)
{
	t_cmd_node	*cmd_node;
	t_list		*cur_cmd_list;
	int			pid;
	int			status;
	int			haspipe;
	int			*lastpipe;

	haspipe = 0;
	cur_cmd_list = cmd_list;
	lastpipe = set_up_pipe();
	while (cur_cmd_list != NULL)
	{
		cmd_node = ((t_cmd_node *)cur_cmd_list->content);
		expand_env(cmd_node->token_list, env_list);
		setup_argv_argc(cmd_node);
		cmd_node->pid = start_command(cmd_node, env_list, haspipe, lastpipe);
		haspipe = ispipe(cmd_node);
		if (haspipe == 1)
			cur_cmd_list = cur_cmd_list->next;
		else
			break ;
	}
	free(lastpipe);
	return (cur_cmd_list);
}

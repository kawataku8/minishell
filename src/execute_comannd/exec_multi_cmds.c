/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:08:16 by takuya            #+#    #+#             */
/*   Updated: 2021/10/10 10:38:34 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cmd.h"
#include "../../include/parse.h"
#include "../../include/env_operations.h"

void	do_single_cmd(t_cmd_node *cmd_node, t_env_list *env_list)
{
	int	exit_status;

	exit_status = execute_buildin(cmd_node, env_list, 2);
	exit(exit_status);
}

// TODO; if execve fails, returns -1. Check errno and Do error handle
void	do_multi_cmd(t_cmd_node *cmd_node, t_env_list *env_list)
{
	char	**dchar_envlist;

	find_abscmd_path(cmd_node->argv);
	dchar_envlist = make_char_envlist(env_list);
	if (execve(cmd_node->argv[0], cmd_node->argv, dchar_envlist) == -1)
	{
		printf("minishell: command not found\n");
		exit(127);
	}
}

// returns each command's pid
pid_t	start_command(t_cmd_node *cmd_node, t_env_list *env_list,
int haspipe, int *lastpipe)
{
	pid_t	pid;
	int		newpipe[2];
	int		exit_status;

	if (ispipe(cmd_node))
		pipe(newpipe);
	pid = fork();
	if (pid == 0)
	{
		dup_lastpipe(haspipe, lastpipe);
		dup_newpipe(cmd_node, newpipe);
		parse_redirect(cmd_node);
		if (get_ft_buildin_idx(cmd_node->argv) > -1)
			do_single_cmd(cmd_node, env_list);
		else
			do_multi_cmd(cmd_node, env_list);
	}
	close_pipe(cmd_node, haspipe, lastpipe, newpipe);
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

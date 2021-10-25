/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmdline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:35:16 by takuya            #+#    #+#             */
/*   Updated: 2021/10/25 23:03:05 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cmd.h"
#include "../../include/parse.h"
#include "../../include/env_operations.h"
#include "../../include/main.h"

extern volatile sig_atomic_t	g_signal_handled;

int	process_single_cmd(t_cmd_node *cmd_node, t_env_list *env_list)
{
	int	exit_status;

	expand_env(cmd_node, env_list);
	if (cmd_node->token_list == NULL)
	{
		my_write_err_msg(2, "minishell: command not found", 0);
		return (127);
	}
	parse_redirect(cmd_node);
	setup_argv_argc(cmd_node);
	exit_status = exec_single_cmd(cmd_node, env_list);
	close_red_filefds(cmd_node->token_list);
	return (exit_status);
}

void	wait_children(int status)
{
	int	res;

	while (1)
	{
		res = wait(&status);
		if (res == -1)
			break ;
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
				g_signal_handled = 0;
		}
		continue ;
	}
}

int	make_exit_status(int status)
{
	int	exit_status;

	exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			exit_status = 130;
			g_signal_handled = 0;
		}
		else if (WTERMSIG(status) == 3)
		{
			printf("Quit: 3\n");
			exit_status = 131;
		}
	}
	return (exit_status);
}

void	process_cmdlist(t_list *cmd_list, t_env_list *env_list)
{
	int			status;
	int			exit_status;
	int			*original_fds;
	t_list		*cur_cmdlist;
	t_cmd_node	*cmd_node;

	exit_status = 0;
	cur_cmdlist = cmd_list;
	while (cur_cmdlist != NULL)
	{
		cmd_node = (t_cmd_node *)cur_cmdlist->content;
		original_fds = dup_original_fds();
		if (cmd_node->op == SCOLON)
			exit_status = process_single_cmd(cmd_node, env_list);
		else
		{
			cur_cmdlist = exec_multi_cmds(cur_cmdlist, env_list);
			waitpid(((t_cmd_node *)(cur_cmdlist->content))->pid, &status, 0);
			exit_status = make_exit_status(status);
			wait_children(status);
		}
		mod_envlist_value("?", ft_itoa(exit_status), env_list);
		reset_fds_orig(original_fds);
		cur_cmdlist = cur_cmdlist->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:08:08 by takuya            #+#    #+#             */
/*   Updated: 2021/10/24 20:53:27 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cmd.h"
#include "../../include/env_operations.h"
#include "../../include/main.h"

extern volatile sig_atomic_t	g_signal_handled;

char	**init_ft_cmd_names(void)
{
	char	**ft_cmd_names;

	ft_cmd_names = ft_split("echo cd pwd export unset env exit", ' ');
	return (ft_cmd_names);
}

int	exec_mycmds(int index, t_cmd_node *cmd_node, t_env_list *env_list)
{
	int	exit_status;

	exit_status = -1;
	if (index == 0)
		exit_status = ft_echo(cmd_node->argv);
	else if (index == 1)
		exit_status = ft_cd(cmd_node->argc, cmd_node->argv, env_list);
	else if (index == 2)
		exit_status = ft_pwd();
	else if (index == 3)
		exit_status = ft_export(cmd_node->argv, env_list);
	else if (index == 4)
		exit_status = ft_unset(cmd_node->argv, env_list);
	else if (index == 5)
		exit_status = ft_env(env_list);
	return (exit_status);
}

int	get_ft_buildin_idx(char **argv)
{
	int		i;
	char	**ft_cmd_names;

	ft_cmd_names = init_ft_cmd_names();
	i = 0;
	while (ft_cmd_names[i] != NULL)
	{
		if (my_strcmp(argv[0], ft_cmd_names[i]) == 0)
			break ;
		i++;
	}
	free_splitstr(ft_cmd_names);
	if (i > 6)
		i = -1;
	return (i);
}

// in parent process -> pa_ch_flag == 1
// in child process -> pa_ch_flag == 2
// TODO: this function need to return exit-status
int	execute_buildin(t_cmd_node *cmd_node, t_env_list *env_list, int pa_ch_flag)
{
	int	ft_buildin_idx;
	int	exit_status;

	exit_status = 0;
	ft_buildin_idx = get_ft_buildin_idx(cmd_node->argv);
	if (ft_buildin_idx > -1)
	{
		if (ft_buildin_idx == 6)
		{
			if (pa_ch_flag == 1)
				exit_status = ft_pa_exit(cmd_node->argv, cmd_node->argc);
			if (pa_ch_flag == 2)
				exit_status = ft_ch_exit(cmd_node->argv, cmd_node->argc);
		}
		else
			exit_status = exec_mycmds(ft_buildin_idx, cmd_node, env_list);
	}
	return (exit_status);
}

int	exec_single_cmd(t_cmd_node *cmd_node, t_env_list *env_list)
{
	int		status;
	int		exit_status;
	char	**dchar_envlist;

	exit_status = 0;
	if (get_ft_buildin_idx(cmd_node->argv) > -1)
		exit_status = execute_buildin(cmd_node, env_list, 1);
	else
	{
		cmd_node->pid = fork();
		if (cmd_node->pid == 0)
		{
			find_abscmd_path(cmd_node->argv, env_list);
			dchar_envlist = make_char_envlist(env_list);
			if (execve(cmd_node->argv[0], cmd_node->argv, dchar_envlist) == -1)
			{
				my_write_err_msg(2, "minishell: command not found", 0);
				exit(127);
			}
		}
		waitpid(cmd_node->pid, &status, 0);
		exit_status = make_exit_status(status);
	}
	return (exit_status);
}

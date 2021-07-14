/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:08:08 by takuya            #+#    #+#             */
/*   Updated: 2021/07/14 20:22:11 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cmd.h"

extern char **environ;

char **init_ft_cmd_names(void)
{
	char **ft_cmd_names;
	ft_cmd_names = ft_split("echo cd pwd export unset env exit",' ');
	return (ft_cmd_names);
}


int exec_mycmds(int index, t_cmd_node *cmd_node,t_env_list *env_list)
{
	if (index == 0)
		ft_echo(cmd_node->argv);
	else if(index == 1)
		ft_cd(cmd_node->argc, cmd_node->argv, env_list);
	else if(index == 2)
		ft_pwd();
	else if(index == 3)
		ft_export(cmd_node->argv, env_list);
	else if(index == 4)
		ft_unset(cmd_node->argv, env_list);
	else if(index == 5)
		ft_env(env_list);
	// else if(index == 6)
	// 	ft_exit();
	
	return -1;
}

int get_ft_buildin_idx(char **argv)
{
	int i;
	char **ft_cmd_names;
	
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

// in parent process -> 1
// in child process -> 2
// TODO: this function need to return exit-status
void execute_buildin(t_cmd_node *cmd_node, t_env_list *env_list, int pa_ch_flag)
{
	int	ft_buildin_idx;

	if ((ft_buildin_idx = get_ft_buildin_idx(cmd_node->argv)) > -1)
	{
		if (ft_buildin_idx == 6)
		{
			if (pa_ch_flag == 1)
				ft_pa_exit(cmd_node->argv, cmd_node->argc);
			if (pa_ch_flag == 2)
				ft_ch_exit(cmd_node->argv, cmd_node->argc);
			return ;
		}
		exec_mycmds(ft_buildin_idx,cmd_node, env_list);
	}
	return ;
}

void exec_single_cmd(t_cmd_node *cmd_node, t_env_list *env_list)
{
	int status;
	int	i;
	char **ft_cmd_names;

	if (get_ft_buildin_idx(cmd_node->argv) > -1)
	{
		execute_buildin(cmd_node, env_list, 1);
		return ;
	}
	else
	{
		cmd_node->pid = fork();
		if (cmd_node->pid == 0)
			execve(cmd_node->argv[0], cmd_node->argv, environ);
		wait(&status);
	}
}


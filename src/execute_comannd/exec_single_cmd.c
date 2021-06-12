/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:08:08 by takuya            #+#    #+#             */
/*   Updated: 2021/06/12 13:31:28 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cmd.h"

extern char **environ;

// char **init_ft_cmd_names(void)
// {
// 	char **ft_cmd_names;
// 	ft_cmd_names = ft_split("echo cd pwd export unset env exit");
// 	return (ft_cmd_names);
// }


// int exec_mycmds(int index, t_cmd_node *cmd_node,t_doubly_list *env_list)
// {
// 	if (index == 0)
// 		return ft_echo();
// 	else if(index == 1)
// 		return ft_cd();
// 	else if(index == 2)
// 		return ft_pwd();
// 	else if(index == 3)
// 		return ft_export();
// 	else if(index == 4)
// 		return ft_unset();
// 	else if(index == 5)
// 		return ft_env();
// 	else if(index == 6)
// 		return ft_exit();
	
// 	return -1;
// }


void exec_single_cmd(t_cmd_node *cmd_node, t_doubly_list *env_list)
{
	int status;
	int	i;
	char **ft_cmd_names;

	// ft_cmd_names = init_ft_cmd_names();

	// while (ft_cmd_names[i] != NULL)
	// {
	// 	if(!(my_strcmp(cmd_node->argv[0],ft_cmd_names[i])))
	// 	{


	// 	}
	// 	i++;
	// }


	// ft_cmdのどれにも当てはまらなかった場合
	// TODO: buildin じゃない場合はexec_multi_cmdsの方で実行？？
	cmd_node->pid = fork();
	
	if (cmd_node->pid == 0)
	{
		execve(cmd_node->argv[0],cmd_node->argv, environ);
	}
	wait(&status);

}
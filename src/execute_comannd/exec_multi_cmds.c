/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:08:16 by takuya            #+#    #+#             */
/*   Updated: 2021/06/13 20:13:52 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cmd.h"


extern char **environ;

int ispipe(t_cmd_node *cur_cmd_node)
{
	if (cur_cmd_node->op == PIPE)
		return 1;
	return 0;
}

void del_cmdnode(void *content)
{
	int i;

	i = 0;
	while(((t_cmd_node*)content)->argv[i] != NULL)
	{
		free(((t_cmd_node*)content)->argv[i]);
		i++;
	}
	free((t_cmd_node*)content);
}

void exec_cmd_inpipe(t_cmd_node *cmd_node, t_env_list *env_list)
{
	if (get_ft_buildin_idx(cmd_node->argv) > -1)
		execute_buildin(cmd_node, env_list);
	else
		execve(cmd_node->argv[0], cmd_node->argv, environ);
}

pid_t	start_command(t_cmd_node *cmd_node, t_env_list *env_list, int haspipe, int lastpipe[2])
{
	pid_t pid;
	int newpipe[2];

	if (ispipe(cmd_node))
		pipe(newpipe);
	pid = fork();
	//子プロセス
	if (pid == 0)
	{
		//左にパイプあり　入力としてpipeに繋がったfd0を使う
		if (haspipe)
		{
			close(lastpipe[1]);
			dup2(lastpipe[0],0);
			close(lastpipe[0]);
		}
		//右にパイプあり　出力をpipeに繋がったfd1に流す
		if (ispipe(cmd_node))
		{
			close(newpipe[0]);
			dup2(newpipe[1], 1);
			close(newpipe[1]);
		}
		// execve(cmd_node->argv[0],cmd_node->argv, environ);
		if (get_ft_buildin_idx(cmd_node->argv) > -1)
			execute_buildin(cmd_node, env_list);
		else
		{
			execve(cmd_node->argv[0], cmd_node->argv, environ);
		}
	}
	
	// 上の子プロセスですでに入出力の受け渡しは終了しているので一個前に使ったpipeをclose
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

t_list *exec_multi_cmds(t_list *cmd_list, t_env_list *env_list)
{
	t_cmd_node *cmd_node;
	int i = 0;
	int pid, status;
	int	haspipe = 0;
	int	lastpipe[2] = { -1, -1 };

	t_list *cur_cmd_list = cmd_list;
	while (cur_cmd_list != NULL)
	{
		cmd_node = ((t_cmd_node*)cur_cmd_list->content);
		expand_env(cmd_node->token_list, env_list);
		//parse_redirect(cur_cmdlist);
		setup_argv_argc(cmd_node);
		cmd_node->pid = start_command(cmd_node, env_list, haspipe, lastpipe);
		if ((haspipe = ispipe(cmd_node)) == 1)
			cur_cmd_list = cur_cmd_list->next;
		else
			break ;
	}
	//一番最後に実行したコマンドのwait
	// waitpid(cmd_node->pid,&status,0);
	// wait(&status);

	return (cur_cmd_list);
}
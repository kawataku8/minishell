/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmdline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:35:16 by takuya            #+#    #+#             */
/*   Updated: 2021/06/30 14:43:12 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cmd.h"
#include "../../include/parse.h"

int process_cmdlist(t_list *cmd_list, t_env_list *env_list)
{
	int status;
	int r;
	int orig_stdin, orig_stdout, orig_stderr;
	t_list *cur_cmdlist;
	t_cmd_node *cmd_node;
	
	cur_cmdlist = cmd_list;
	while(cur_cmdlist != NULL)
	{
		cmd_node = (t_cmd_node*)cur_cmdlist->content;

		// コマンド実行後にfdを初期値に戻すために、初期値を保存
		save_orig_fd(&orig_stdin, &orig_stdout, &orig_stderr);

		printf("====================================\n");
		if (cmd_node->op == SCOLON)
		{
			expand_env(cmd_node->token_list, env_list);
			parse_redirect(cmd_node->token_list);
			setup_argv_argc(cmd_node);
			exec_single_cmd(cmd_node, env_list);
		}
		else
		{
			cur_cmdlist = exec_multi_cmds(cur_cmdlist,env_list);
			// waitpid(((t_cmd_node*)cur_cmdlist->content)->pid,&status,0);
			// TODO:forkした回数child processをwaitして回収
			// しないと出力の順番が崩れる
			while ((r = wait(&status)) != -1)
			{
				// printf("STATUS:%d\n", r);
				continue ;
			}
		}
	
		//リダイレクトによって変更したデフォfd(0,1,2)のリセット
		// save_original_fd()で保存した値を使用
		reset_fds_orig(orig_stdin, orig_stdout, orig_stderr);
		cur_cmdlist = cur_cmdlist->next;
	}
	
	return 0;
}

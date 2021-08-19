/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmdline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:35:16 by takuya            #+#    #+#             */
/*   Updated: 2021/08/18 00:01:00 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cmd.h"
#include "../../include/parse.h"
#include "../../include/env_operations.h"

int process_cmdlist(t_list *cmd_list, t_env_list *env_list)
{
	int status;
	int r;
	int exit_status;
	int orig_stdin, orig_stdout, orig_stderr;
	t_list *cur_cmdlist;
	t_cmd_node *cmd_node;

	exit_status = 0;
	cur_cmdlist = cmd_list;
	while(cur_cmdlist != NULL)
	{
		cmd_node = (t_cmd_node*)cur_cmdlist->content;

		// コマンド実行後にfdを初期値に戻すために、初期値を保存
		save_orig_fd(&orig_stdin, &orig_stdout, &orig_stderr);

		// printf("====================================\n");
		// if cmd_node->op is SCOLON, it's single command
		// others are pipe list
		if (cmd_node->op == SCOLON)
		{
			expand_env(cmd_node->token_list, env_list);
			parse_redirect(cmd_node->token_list);
			setup_argv_argc(cmd_node);
			// TODO: exec_single_cmdからコマンドの終了ステータスを受け取る
			exit_status = exec_single_cmd(cmd_node, env_list);

			// exec_single_cmd(cmd_node, env_list);
			close_red_filefds(cmd_node->token_list);
		}
		else
		{
			cur_cmdlist = exec_multi_cmds(cur_cmdlist,env_list);
			// waitpid(((t_cmd_node*)cur_cmdlist->content)->pid,&status,0);
			
			// TODO:一番最後(pipe_listの右端)のコマンドの終了ステータスをstatusから取得して,
			// exit_statusに入れる
			// exit_status = _____();
			waitpid(((t_cmd_node*)(cur_cmdlist->content))->pid, &status, 0);
			exit_status = WEXITSTATUS(status);
			while ((r = wait(&status)) != -1)
			{
				// printf("STATUS:%d\n", r);
				continue ;
			}
			// TODO: cur_cmdlist をopがセミコロンになるまで進める
			// A|B|C  でBで止まってるパターンある(BでCtrl C)
		}

		// TODO:env_listに入っている終了ステータス(?=0)をexit_statusに更新
		mod_envlist_value("?",ft_itoa(exit_status),env_list);
	
		//リダイレクトによって変更したデフォfd(0,1,2)のリセット
		// save_original_fd()で保存した値を使用
		reset_fds_orig(orig_stdin, orig_stdout, orig_stderr);
		cur_cmdlist = cur_cmdlist->next;
	}
	
	return 0;
}

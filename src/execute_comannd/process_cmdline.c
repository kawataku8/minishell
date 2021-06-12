/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmdline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:35:16 by takuya            #+#    #+#             */
/*   Updated: 2021/06/12 13:24:39 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cmd.h"

int process_cmdlist(t_list *cmd_list, t_doubly_list *env_list)
{
	t_list *cur_cmdlist;
	t_cmd_node *cmd_node;
	
	cur_cmdlist = cmd_list;
	while(cur_cmdlist != NULL)
	{
		cmd_node = (t_cmd_node*)cur_cmdlist->content;


		printf("====================================\n");
		if (cmd_node->op == SCOLON)
		{
			expand_env(cmd_node->token_list, env_list);
			//parse_redirect(cur_cmdlist);
			setup_argv_argc(cmd_node);
			exec_single_cmd(cmd_node, env_list);
		}
		else
		{
			cur_cmdlist = exec_multi_cmds(cur_cmdlist,env_list);
		}

		//リダイレクトによって変更したデフォfd(0,1,2)のリセット
		//reset_fds();
		cur_cmdlist = cur_cmdlist->next;
	}
	
	return 0;
}

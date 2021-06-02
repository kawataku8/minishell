/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmdline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:35:16 by takuya            #+#    #+#             */
/*   Updated: 2021/06/01 16:50:16 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cmd.h"


//process_cmdline(char *usr_input)
int exec_cmdline(t_list *cmd_list)
{
	
	// while()
	//parse_env();
	//parse_redirect();
	
	// if (single)
	// {
	// 	exec_single_cmd();
	// }
	// else
	exec_multi_cmds(cmd_list);

	//リダイレクトによって変更したデフォfd(0,1,2)のリセット
	//reset_fds();
	
	return 0;
}
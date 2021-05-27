/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 13:54:18 by takuya            #+#    #+#             */
/*   Updated: 2021/05/18 13:07:16 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cmd.h"


int main(void)
{
	
	// t_cmd_list cmds_list;
	// t_cmd_node *cmd_node;

	// cmd_node = (t_cmd_node*)malloc(sizeof(t_cmd_node));
	// cmd_node->argv = ft_split("/bin/ls",' ');
	// cmds_list.head = cmd_node;

	// cmd_node = (t_cmd_node*)malloc(sizeof(t_cmd_node));
	// cmd_node->argv = ft_split("/usr/bin/grep .c", ' ');
	// cmds_list.head->next = cmd_node;

	// cmd_node = (t_cmd_node*)malloc(sizeof(t_cmd_node));
	// cmd_node->argv = ft_split("/usr/bin/wc", ' ');
	// cmds_list.head->next->next = cmd_node;
	// cmds_list.head->next->next->next = NULL;


	t_process *process;
	t_list *cmd_list = NULL;
	t_cmd_node *cmd_node;

	cmd_node = (t_cmd_node*)malloc(sizeof(t_cmd_node));
	cmd_node->argv = ft_split("/bin/ls",' ');
	ft_lstadd_back(&cmd_list,ft_lstnew((void*)cmd_node));

	cmd_node = (t_cmd_node*)malloc(sizeof(t_cmd_node));
	cmd_node->argv = ft_split("/usr/bin/grep .out", ' ');
	ft_lstadd_back(&cmd_list,ft_lstnew((void*)cmd_node));

	cmd_node = (t_cmd_node*)malloc(sizeof(t_cmd_node));
	cmd_node->argv = ft_split("/usr/bin/wc", ' ');
	ft_lstadd_back(&cmd_list,ft_lstnew((void*)cmd_node));

	process->cmd_listhead = cmd_list;

	
	// TODO:process_redirect();
	// redirect out test
	// int out_fd;
	// out_fd = open("output", O_CREAT | O_RDWR, S_IRWXU);
	// close(1);
	// dup2(out_fd, 1);
	// close(out_fd);

	//redirect in test
	// int in_fd;
	// in_fd = open("output", O_RDONLY);
	// close(0);
	// dup2(in_fd, 0);
	// close(in_fd);

	// while(1)
	// {
	// 	usr_input = get_usrinput();
	// 	process =  parse(usr_input);


	// 	//cmds_listをトラバースしてそれぞれのコマンド実行
	// 	exec_cmdline(&cmds_list);

	// }


	exec_cmdline(process);

	ft_lstclear(&process->cmd_listhead,&del_cmdnode);

	return 0;
}
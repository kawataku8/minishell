/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 13:54:18 by takuya            #+#    #+#             */
/*   Updated: 2021/05/14 13:59:42 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cmd.h"


int main(void)
{
	
	t_cmd_list cmds_list;
	t_cmd_node *cmd_node;

	cmd_node = (t_cmd_node*)malloc(sizeof(t_cmd_node));
	//TODO make_cmd_node("/bin/ls ./")に置き換え
	// cmd_node->argv = ft_split("/bin/ls ./",' ');
	cmd_node->argv = ft_split("/bin/ls",' ');
	cmds_list.head = cmd_node;
	cmd_node = (t_cmd_node*)malloc(sizeof(t_cmd_node));
	cmd_node->argv = ft_split("/usr/bin/grep .c", ' ');
	cmds_list.head->next = cmd_node;
	cmd_node = (t_cmd_node*)malloc(sizeof(t_cmd_node));
	cmd_node->argv = ft_split("/usr/bin/wc", ' ');
	// cmd_node->argv = argv3;
	cmds_list.head->next->next = cmd_node;

	cmds_list.head->next->next->next = NULL;


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

	exec_multi_cmds(&cmds_list);


	free_cmd_list(&cmds_list);

	return 0;
}
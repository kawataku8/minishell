/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mystruct.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 07:45:47 by takuya            #+#    #+#             */
/*   Updated: 2021/06/13 12:46:01 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSTRUCT_H
# define MYSTRUCT_H

#include "../libft/libft.h"

//一つのコマンドを表す構造体
// "echo hello" -> argv[0]:echo, argv[1]:hello
//• argc > 1 の場合は
//next != NULL 右にpipe | を持つ
//next == NULL pipe cmdsの最後のコマンド
typedef struct	s_cmd_node
{
	pid_t 				pid;
	int		op;
	char *red_in_filepath;
	char *red_out_filepath;
	char *red_err_filepath;
	int					argc;
	char				**argv;
	t_list				*token_list;
}				t_cmd_node;

// typedef struct s_process
// {
// 	t_list *cmd_listhead;
// }				t_process;

typedef struct s_token
{
	int		type;
	char	*word;
}				t_token;

typedef struct s_env_node
{
	char	*key;
	char	*value;
	struct s_env_node *next;
	struct s_env_node *prev;
}				t_env_node;

typedef struct      s_env_list
{
	t_env_node *head;
	t_env_node *tail;
}                   t_env_list;

#endif
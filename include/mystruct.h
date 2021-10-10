/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mystruct.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 07:45:47 by takuya            #+#    #+#             */
/*   Updated: 2021/10/10 01:27:42 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSTRUCT_H
# define MYSTRUCT_H

# 	include "../libft/libft.h"

typedef struct s_cmd_node
{
	pid_t	pid;
	int		op;
	int		argc;
	char	**argv;
	t_list	*token_list;
	char	*heredoc_filepath;
}				t_cmd_node;

typedef struct s_token
{
	int		type;
	char	*word;
}				t_token;

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
	struct s_env_node	*prev;
}				t_env_node;

typedef struct s_env_list
{
	t_env_node	*head;
	t_env_node	*tail;
}					t_env_list;

#endif
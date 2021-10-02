/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:18:00 by takuya            #+#    #+#             */
/*   Updated: 2021/10/02 13:19:05 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env_operations.h"

int	get_chrindex(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

t_env_list	*make_envlist(char **envp)
{
	t_env_list	*env_list;
	t_env_node	*new_envnode;
	char		*key;
	char		*value;
	int			eql_idx;

	env_list = (t_env_list *)malloc(sizeof(t_env_list));
	env_list->head = NULL;
	env_list->tail = NULL;
	while (*envp != NULL)
	{
		eql_idx = get_chrindex(*envp, '=');
		key = ft_substr(*envp, 0, eql_idx);
		value = ft_substr(*envp, eql_idx + 1, ft_strlen(*envp) - eql_idx + 1);
		new_envnode = make_node(key, value);
		insert_end(env_list, new_envnode);
		envp++;
	}
	key = ft_strdup("?");
	value = ft_strdup("0");
	new_envnode = make_node(key, value);
	insert_end(env_list, new_envnode);
	return (env_list);
}

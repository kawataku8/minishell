/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd_oldpwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:52:16 by stakabay          #+#    #+#             */
/*   Updated: 2021/10/13 23:46:25 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"

char	*set_oldpwd_path(t_env_list *list)
{
	t_env_node	*node;
	char		*path;

	node = serch_nodes(list, "OLDPWD");
	if (!node)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", STD_ERR);
		return (NULL);
	}
	path = ft_strdup(node->value);
	return (path);
}

void	set_pwd_and_oldpwd(t_env_list *list)
{
	t_env_node	*node;
	t_env_node	*ndptr;

	node = serch_nodes(list, "PWD");
	ndptr = serch_nodes(list, "OLDPWD");
	if (!ndptr)
	{
		ndptr = make_env_node("OLDPWD", node->value);
		if (!ndptr)
			exit(malloc_error());
		insert_end(list, ndptr);
	}
	else
	{
		ndptr->value = ft_strdup(node->value);
		if (!ndptr->value)
			exit(malloc_error());
		node->value = ft_strdup(getcwd(NULL, 0));
		if (!node->value)
			exit(malloc_error());
	}
}

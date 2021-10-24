/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd_oldpwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:52:16 by stakabay          #+#    #+#             */
/*   Updated: 2021/10/24 20:16:54 by stakabay         ###   ########.fr       */
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

void	set_oldpwd(t_env_list *list, t_env_node *node, t_env_node *ndptr)
{
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
	}
}

void	set_pwd_and_oldpwd(t_env_list *list)
{
	t_env_node	*node;
	t_env_node	*ndptr;
	char		*cwdpath;

	node = serch_nodes(list, "PWD");
	ndptr = serch_nodes(list, "OLDPWD");
	set_oldpwd(list, node, ndptr);
	cwdpath = getcwd(NULL, 0);
	if (!cwdpath)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", STD_ERR);
		ft_putstr_fd("getcwd: cannot access parent directories: ", STD_ERR);
		ft_putendl_fd("No such file or directory", STD_ERR);
	}
	else
		node->value = ft_strdup(cwdpath);
	if (!node->value)
		exit(malloc_error());
}

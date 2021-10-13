/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:52:18 by stakabay          #+#    #+#             */
/*   Updated: 2021/10/13 23:51:09 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"

char	*set_path(char **argv, int argc, t_env_list *list)
{
	t_env_node	*node;
	char		*path;

	if (argc == 1 || !ft_strncmp(argv[1], "--", 2))
	{
		node = serch_nodes(list, "HOME");
		path = ft_strdup(node->value);
	}
	else if (!ft_strncmp(argv[1], "-", 1))
		path = set_oldpwd_path(list);
	else if (argv[1][0] == '~')
	{
		node = serch_nodes(list, "HOME");
		argv[1]++;
		path = ft_strjoin(node->value, argv[1]);
	}
	else
		path = ft_strdup(argv[1]);
	if (!path)
		exit(malloc_error());
	return (path);
}

int	is_valid_arg(int argc, t_env_list *list)
{
	if (argc == 1 && !serch_nodes(list, "HOME"))
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (FALSE);
	}
	return (SUCCESS);
}

int	chdir_error_message(char *path)
{
	if (errno == EACCES)
	{
		put_string_fd("minishell: cd: ", STD_ERR);
		put_string_fd(path, STD_ERR);
		ft_putendl_fd(": Permission denied", STD_ERR);
	}
	else if (errno == ENOENT)
	{
		put_string_fd("minishell: cd: ", STD_ERR);
		put_string_fd(path, STD_ERR);
		ft_putendl_fd(": No such file or directory", STD_ERR);
	}
	else if (errno == ENAMETOOLONG)
	{
		put_string_fd("minishell: cd: ", STD_ERR);
		put_string_fd(path, STD_ERR);
		ft_putendl_fd(": File name too long", STD_ERR);
	}
	else if (errno == ENOTDIR)
	{
		put_string_fd("minishell: cd: ", STD_ERR);
		put_string_fd(path, STD_ERR);
		ft_putendl_fd(": Not a directory", STD_ERR);
	}
	return (GENERAL_ERRORS);
}

int	ft_cd(int argc, char **argv, t_env_list *list)
{
	char		*path;

	if (!is_valid_arg(argc, list))
		return (ERROR);
	path = set_path(argv, argc, list);
	if (chdir(path) == -1)
		return (chdir_error_message(path));
	set_pwd_and_oldpwd(list);
	free(path);
	return (SUCCEEDED);
}

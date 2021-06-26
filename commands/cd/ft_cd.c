/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 08:38:07 by stakabay          #+#    #+#             */
/*   Updated: 2021/06/26 12:29:41 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"

// 	1. to home directory >> no args || "--"
// 	2. to previous directory >> only'-'
// 		bash: cd: OLDPWD not set
// 	3. replace with home directory path >> '~' || !arg

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
	if (argc >= 3)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (FALSE);
	}
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
	return (FALSE);
}

int	ft_cd(int argc, char **argv, t_env_list *list)
{
	char		*path;

	if (!is_valid_arg(argc, list))
		return (ERROR);
	path = set_path(argv, argc, list);
	if (chdir(path) == -1)
		return (chdir_error_message(path));
	set_pwd_and_oldpwd(list, path);
	free(path);
	return (SUCCEEDED);
}

/*
int		main(int argc, char **argv, char **envp)
{
	t_env_list	env_list;
	t_env_node	*node;
	char		*keybuf;
	char		*valuebuf;
	char		*ptr;

	while (*envp)
	{
		ptr = ft_strchr(*envp, '=');
		keybuf = ft_substr(*envp, 0, ptr - *envp);
		valuebuf = ft_strdup(*envp + (ptr - *envp + 1));
		node = make_env_node(keybuf, valuebuf);
		//printf("declare -x %s=", node->key);
		//printf("%s\n", node->value);
		insert_end(&env_list, node);
		node = node->next;
		envp++;
	}
	if (argc >= 2)
	{
		argv++;
		argc--;
	}	
	printf("befor cwd :%s\n", getcwd(NULL, 0));
	node = serch_nodes(&env_list, "PWD");
	printf("befor PWD :%s\n", node->value);
	if ((node = serch_nodes(&env_list, "OLDPWD")) != NULL)
		printf("befor OLDPWD :%s\n", node->value);
	ft_cd(argc, argv, &env_list);
	printf("after cwd :%s\n", getcwd(NULL, 0));
	node = serch_nodes(&env_list, "PWD");
	printf("after PWD :%s\n", node->value);
	if ((node = serch_nodes(&env_list, "OLDPWD")) != NULL)
		printf("after OLDPWD :%s\n", node->value);
	return (0);
}
*/

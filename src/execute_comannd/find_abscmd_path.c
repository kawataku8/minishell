/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_abscmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 15:52:37 by takuya            #+#    #+#             */
/*   Updated: 2021/10/24 19:20:21 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cmd.h"

char	*make_cmd_path(char *target_dir, char *cmd_name)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*res;

	res = NULL;
	dir = opendir(target_dir);
	if (dir == NULL)
	{
		perror("opendir() error");
		return (res);
	}
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (my_strcmp(entry->d_name, cmd_name) == 0)
			res = ft_strjoin(target_dir, cmd_name);
	}
	closedir(dir);
	return (res);
}

char	*gene_abscmd_path(char *path, char *cmd_argv)
{
	char	*path_tmp;
	char	*abs_cmd_path;

	path_tmp = ft_strjoin(path, "/");
	abs_cmd_path = make_cmd_path(path_tmp, cmd_argv);
	free(path_tmp);
	return (abs_cmd_path);
}

// find an absolute path of command
void	find_abscmd_path(char **cmd_argv, t_env_list *env_list)
{
	int		i;
	char	*abs_cmd_path;
	char	**path_list;
	char	*path_value;

	path_value = get_value_from_envlist("PATH", env_list);
	if (path_value == NULL)
		return ;
	path_list = ft_split(path_value, ':');
	abs_cmd_path = NULL;
	i = 0;
	while (path_list[i] != NULL && abs_cmd_path == NULL)
	{
		abs_cmd_path = gene_abscmd_path(path_list[i], cmd_argv[0]);
		i++;
	}
	if (abs_cmd_path != NULL)
	{
		free(cmd_argv[0]);
		cmd_argv[0] = abs_cmd_path;
	}
	free(path_value);
	free_splitstr(path_list);
}

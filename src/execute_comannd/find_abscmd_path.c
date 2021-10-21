/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_abscmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 15:52:37 by takuya            #+#    #+#             */
/*   Updated: 2021/10/21 14:50:34 by takuya           ###   ########.fr       */
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

// find an absolute path of command
// ascii 47 == '/'
void	find_abscmd_path(char **cmd_argv)
{
	char	*abs_cmd_path;

	abs_cmd_path = NULL;
	if (cmd_argv[0][0] == 47)
		return ;
	abs_cmd_path = make_cmd_path("/bin/", cmd_argv[0]);
	if (abs_cmd_path == NULL)
		abs_cmd_path = make_cmd_path("/usr/bin/", cmd_argv[0]);
	if (abs_cmd_path == NULL)
		return ;
	free(cmd_argv[0]);
	cmd_argv[0] = abs_cmd_path;
}

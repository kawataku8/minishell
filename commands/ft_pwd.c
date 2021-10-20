/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:50:51 by stakabay          #+#    #+#             */
/*   Updated: 2021/10/14 09:39:19 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"

int	ft_pwd(void)
{
	char	*pwd_buf;

	pwd_buf = getcwd(NULL, 0);
	if (pwd_buf == NULL)
	{
		if (errno == ENOENT)
			ft_putendl_fd("No such file or directory", STD_ERR);
		if (errno == EACCES)
			ft_putendl_fd("Permission denied", STD_ERR);
		if (errno == ENAMETOOLONG)
			ft_putendl_fd("File name too long", STD_ERR);
		return (ERROR);
	}
	ft_putendl_fd(pwd_buf, 1);
	free(pwd_buf);
	return (SUCCEEDED);
}

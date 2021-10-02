/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:51:00 by stakabay          #+#    #+#             */
/*   Updated: 2021/09/19 21:51:03 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"

int	check_newline_flag(char *arg)
{
	int		i;	

	i = 0;
	if (arg == NULL)
		return (0);
	if (arg[0] == '-')
	{
		while (arg[++i] == 'n')
			if (arg[i + 1] == '\0')
				return (1);
	}
	return (0);
}

int	ft_echo(char **argv)
{
	int		n_opt;
	int		idx;

	idx = 0;
	n_opt = check_newline_flag(argv[1]);
	if (n_opt)
		idx = 1;
	while (argv[++idx])
	{
		put_string_fd(argv[idx], 1);
		if (argv[idx + 1])
			put_space(1);
	}
	if (!n_opt)
		put_endl(1);
	return (SUCCEEDED);
}

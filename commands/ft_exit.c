/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:50:54 by stakabay          #+#    #+#             */
/*   Updated: 2021/10/17 16:54:48 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"

int	is_num(char *argv)
{
	int		digit;

	digit = 0;
	if (argv == NULL)
		return (FALSE);
	if (*argv == '-' || *argv == '+')
		argv++;
	while (*argv)
	{
		if (*argv < '0' || '9' < *argv)
			return (FALSE);
		argv++;
		digit++;
	}
	if (digit >= 20)
		return (FALSE);
	return (TRUE);
}

int	ft_ch_exit(char **argv, int argc)
{
	ft_putendl_fd("exit", STD_OUT);
	if (!is_num(argv[1]) && argv[1])
	{
		put_string_fd("minishell: exit: ", STD_ERR);
		put_string_fd(argv[1], STD_ERR);
		ft_putendl_fd(": numeric argument required", STD_ERR);
		exit (INVALID_ARGUMENT);
	}
	if (argc >= 3)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STD_ERR);
		exit (GENERAL_ERRORS);
	}
	if (!argv[1])
		exit(SUCCEEDED);
	if (argv[1])
		exit(ft_atoi(argv[1]) & 255);
	return (SUCCEEDED);
}

int	ft_pa_exit(char **argv, int argc)
{
	ft_putendl_fd("exit", STD_ERR);
	if (!is_num(argv[1]) && argv[1])
	{
		put_string_fd("minishell: exit: ", STD_ERR);
		put_string_fd(argv[1], STD_ERR);
		ft_putendl_fd(": numeric argument required", STD_ERR);
		exit (INVALID_ARGUMENT);
	}
	if (argc >= 3)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STD_ERR);
		return (GENERAL_ERRORS);
	}
	if (!argv[1])
		exit(SUCCEEDED);
	if (argv[1])
		exit(ft_atoi(argv[1]) & 255);
	return (SUCCEEDED);
}

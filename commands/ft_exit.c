/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 13:44:01 by stakabay          #+#    #+#             */
/*   Updated: 2021/07/14 20:32:10 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"

//exit statusはlong型の最大値までしか取れない。(19桁)

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
		exit (ERROR);
	}
	if (!argv[1])
		exit(SUCCEEDED);
	if (argv[1])
		exit(ft_atoi(argv[1]) & 255);
	return (SUCCEEDED);
}

//引数が何個であろうと、先頭の引数が数値でない場合はエラーをはくが、exitは成功する。
//exit statusは0-255で256以上は255の余剰となる
int	ft_pa_exit(char **argv, int argc)
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
		return (ERROR);
	}
	if (!argv[1])
		exit(SUCCEEDED);
	if (argv[1])
		exit(ft_atoi(argv[1]) & 255);
	return (SUCCEEDED);
}

// int	main(int argc, char **argv)
// {
// 	argv++;
// 	argc--;
// 	ft_pa_exit(argv, argc);
// 	return (0);
// }

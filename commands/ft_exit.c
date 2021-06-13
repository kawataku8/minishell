#include "command.h"

int		is_num(char *argv)
{
	int		digit;

	digit = 0;
	if (argv == NULL)
		return (0);
	if (*argv == '-' ||*argv == '+')
		argv++;
	while(*argv)
	{
		if (*argv < '0' || '9' < *argv)
			return (FALSE);
		argv++;
		digit++;
	}
	//exit statusはlong型の最大値までしか取れない。(19桁)
	if (digit >= 20)
		return (FALSE);
	return (TRUE);
}

int		ft_ch_exit(char **argv, int argc)
{

	put_string_fd("exit\n", 1);
	
	//引数が何個であろうと、先頭の引数が数値でない場合はエラーをはくが、exitは成功する。
	if (!is_num(argv[1]) && argv[1])
	{
		put_string_fd("minishell: exit: ", STD_ERR);
		put_string_fd(argv[1], STD_ERR);
		put_string_fd(": numeric argument required\n", STD_ERR);
		exit (INVALID_ARGUMENT);
	}
	if (argc >= 3)
	{
		put_string_fd("minishell: exit: too many arguments\n", STD_ERR);
		exit (GENERAL_ERRORS);
	}

	if (!argv[1])
	{
		exit(EXIT_SUCCESS);
	}
	//exit statusは0-255で256以上は255の余剰となる
	if (argv[1])
		exit(ft_atoi(argv[1]) & 255);
	return (1);
}

int		ft_pa_exit(char **argv, int argc)
{

	put_string_fd("exit\n", 1);
	
	//引数が何個であろうと、先頭の引数が数値でない場合はエラーをはくが、exitは成功する。
	if (!is_num(argv[1]) && argv[1])
	{
		put_string_fd("minishell: exit: ", STD_ERR);
		put_string_fd(argv[1], STD_ERR);
		put_string_fd(": numeric argument required\n", STD_ERR);
		exit (INVALID_ARGUMENT);
	}
	if (argc >= 3)
	{
		put_string_fd("minishell: exit: too many arguments\n", STD_ERR);
		return (FALSE);
	}

	if (!argv[1])
	{
		exit(EXIT_SUCCESS);
	}
	//exit statusは0-255で256以上は255の余剰となる
	if (argv[1])
		exit(ft_atoi(argv[1]) & 255);
	return (1);
}

int		main(int argc, char **argv)
{
	argv++;
	argc--;
	ft_pa_exit(argv, argc);
	
	return (0);
}
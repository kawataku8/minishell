#include <unistd.h>
#include <stdio.h>

void	put_string_fd(char *str, int fd);
void	put_space(int fd);
void	put_endl(int fd);

int			check_newline_flag(char *arg)
{
	int		i;	

	i = 0;
	if (arg[0] == '-')
	{
		//nが何個続いても対応する　ex; echo -nnnnnnnn a
		while (arg[++i] == 'n')
			if (arg[i + 1] == '\0')
				return (1);
	}
	return (0);
}

void		ft_echo(int argc, char **argv)
{
	//-n option フラグ
	int		n_opt;
	int		idx;
	
	idx = 0;
	//argv[0]が"-n"かどうかをチェックし、idxをひとつ進める。
	//echo -nnnnnnnn -nnnnnnnn a　はどうする？
	if ((n_opt = check_newline_flag(argv[1])))
		idx = 1;
	//echoに続く文字列を表示する
	//putendlで一発で表示させてもいい？
	while (argv[++idx])
	{
		put_string_fd(argv[idx], 1);
		if (argv[idx + 1])
			put_space(1);
	}
	if (!n_opt)
		put_endl(1);	
}


// int		main(int argc, char **argv)
// {
// 	argv++;
// 	if (strcmp(argv[0],"echo") == 0) 
// 	ft_echo(argv);
// 	return (0);
// }
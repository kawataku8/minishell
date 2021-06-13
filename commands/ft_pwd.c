#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
//カレントディレクトリを取得して表示するのみ

void	put_string_fd(char *str, int fd);
void	put_endl(int fd);

void		ft_pwd(char **argv)
{
	char	*pwd_buf;

	if ((pwd_buf = getcwd(NULL, 0)) == NULL)
	{
		perror("");
		exit(1);
	}
	put_string_fd(pwd_buf, 1);
	put_endl(1);
	free(pwd_buf);
}

// int		main(int argc, char **argv)
// {
// 	ft_pwd(argv);
// 	chdir("/Users/user/Desktop/42tokyo");
// 	ft_pwd(argv);
// 	return(0);
// }
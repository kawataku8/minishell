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

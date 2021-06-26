#include "../include/command.h"

void	put_string_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}

void	put_space(int fd)
{
	write(fd, " ", 1);
}

void	put_endl(int fd)
{
	write(fd, "\n", 1);
}

t_env_node		*serch_nodes(t_env_list *list, char *keybuf)
{
	t_env_node		*ndptr;

	ndptr = list->head;
	while (ndptr)
	{
		if (!(ft_strncmp(ndptr->key, keybuf, ft_strlen(keybuf))))
		{
			//keyがリストの中にあった場合
			if (ndptr->value)
				return (ndptr);
		}
		ndptr = ndptr->next;
	}
	return (NULL);
}

int	malloc_error(void)
{
	put_string_fd("minishell: malloc error", STD_ERR);
	return (GENERAL_ERRORS);
}

int		is_valid_env_key(char *key)
{
	if (!key)
		return (FALSE);
	if ('0' <= *key && *key <= '9')
		return (FALSE);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (FALSE);
		++key;
	}
	return (TRUE);
}
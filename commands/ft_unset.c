#include "../include/command.h"

int	ft_unset(char **argv, t_env_list *list)
{
	t_env_node	*node;
	int			renum;

	renum = SUCCEEDED;
	while (*argv)
	{
		if (!is_valid_env_key(*argv))
		{
			put_string_fd("minishell: export: \'", STD_ERR);
			put_string_fd(*argv, STD_ERR);
			ft_putendl_fd("\': not a valid identifier", STD_ERR);
			renum = ERROR;
		}
		else
		{
			node = serch_nodes(list, *argv);
			if (node)
			{
				remove_env_node(list, node);
			}
		}
		argv++;
	}
	return (renum);
}

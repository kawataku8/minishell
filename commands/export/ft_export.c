/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:52:09 by stakabay          #+#    #+#             */
/*   Updated: 2021/09/19 21:52:11 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"

t_env_node	*make_newnode_from_arg(char *argv, t_env_node *node)
{
	char		*ptr;
	char		*keybuf;
	char		*valuebuf;

	ptr = ft_strchr(argv, '=');
	if (ptr != NULL)
	{
		keybuf = ft_substr(argv, 0, ptr - argv);
		valuebuf = ft_strdup(argv + (ptr - argv + 1));
		node = make_env_node(keybuf, valuebuf);
		if (!keybuf || !valuebuf || !node)
			exit(malloc_error());
	}
	else
	{
		keybuf = ft_strdup(argv);
		valuebuf = NULL;
		node = make_env_node(keybuf, valuebuf);
		if (!keybuf || !node)
			exit(malloc_error());
	}
	free(keybuf);
	free(valuebuf);
	return (node);
}

void	export_identifier_error(t_env_node *node, int *renum, char *argv)
{
	put_string_fd("minishell: export: \'", STD_ERR);
	put_string_fd(argv, STD_ERR);
	ft_putendl_fd("\': not a valid identifier", STD_ERR);
	free(node->key);
	free(node->value);
	free(node);
	*renum = ERROR;
}

void	insert_node_to_list(t_env_list *list, t_env_node *node)
{
	t_env_node	*ndptr;

	ndptr = serch_nodes(list, node->key);
	if (ndptr == NULL)
		insert_end(list, node);
	else if (node->value)
	{
		ndptr->value = ft_strdup(node->value);
		if (ndptr->value == NULL)
			exit(malloc_error());
		free(node);
	}
}

int	ft_export(char **argv, t_env_list *list)
{
	t_env_node	*node;
	int			renum;
	int			i;

	i = 1;
	renum = SUCCEEDED;
	if (!argv[1])
		export_env_list(list);
	while (argv[i])
	{
		node = make_newnode_from_arg(argv[i], node);
		if ((is_valid_env_key(node->key)) == FALSE)
			export_identifier_error(node, &renum, *argv);
		else
			insert_node_to_list(list, node);
		i++;
	}
	return (renum);
}

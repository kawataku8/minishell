/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:52:07 by stakabay          #+#    #+#             */
/*   Updated: 2021/09/19 21:52:08 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"

char	**malloc_arr(t_env_node *node)
{
	char		**env_arr;
	int			envcount;

	envcount = 0;
	while (node != NULL)
	{
		envcount++;
		node = node->next;
	}
	env_arr = malloc(sizeof(char *) * envcount + 1);
	if (env_arr == NULL)
		exit(malloc_error());
	return (env_arr);
}

void	list_to_arr(t_env_node *node, char **env_arr)
{
	int			i;

	i = 0;
	while (node != NULL)
	{
		if (ft_strncmp(node->key, "_", 1) && ft_strncmp(node->key, "?", 1))
		{
			env_arr[i] = ft_strdup(node->key);
			if (env_arr[i] == NULL)
				exit(malloc_error());
			if (node->value)
			{
				env_arr[i] = ft_strjoin(env_arr[i], "=\"");
				env_arr[i] = ft_strjoin(env_arr[i], node->value);
				env_arr[i] = ft_strjoin(env_arr[i], "\"");
				if (!env_arr[i])
					exit(malloc_error());
			}
			i++;
		}
		node = node->next;
	}
	env_arr[i] = NULL;
	return ;
}

char	**make_env_arr(t_env_list *list)
{
	char		**env_arr;
	t_env_node	*node;

	node = list->head;
	env_arr = malloc_arr(node);
	merge_sort(&node);
	list->head = node;
	list_to_arr(node, env_arr);
	return (env_arr);
}

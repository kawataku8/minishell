/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:52:12 by stakabay          #+#    #+#             */
/*   Updated: 2021/09/19 21:52:13 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"

void	print_env_arr(char **env_arr)
{
	int	i;

	i = 0;
	while (env_arr[i])
	{
		put_string_fd("declare -x ", STD_OUT);
		ft_putendl_fd(env_arr[i], STD_OUT);
		i++;
	}
}

t_env_list	*dup_list(t_env_list *source_list)
{
	t_env_list	*dest_list;
	t_env_node	*snode;
	t_env_node	*dnode;

	dest_list = (t_env_list *)malloc(sizeof(t_env_list));
	dest_list->head = NULL;
	dest_list->tail = NULL;
	dnode = NULL;
	snode = source_list->head;
	while (snode != NULL)
	{
		dnode = make_env_node(snode->key, snode->value);
		insert_end(dest_list, dnode);
		snode = snode->next;
	}
	return (dest_list);
}

void	export_env_list(t_env_list *list)
{
	char		**env_arr;
	char		**ptr;
	t_env_list	*copy_list;

	copy_list = dup_list(list);
	env_arr = make_env_arr(copy_list);
	clear_env_list(copy_list);
	print_env_arr(env_arr);
	ptr = env_arr;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(env_arr);
}

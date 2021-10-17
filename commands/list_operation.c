/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:50:45 by stakabay          #+#    #+#             */
/*   Updated: 2021/10/17 16:29:41 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"

t_env_node	*serch_nodes(t_env_list *list, char *keybuf)
{
	t_env_node		*ndptr;

	ndptr = list->head;
	while (ndptr)
	{
		if (!(ft_strncmp(ndptr->key, keybuf, ft_strlen(keybuf) + 1)))
		{
			return (ndptr);
		}
		ndptr = ndptr->next;
	}
	return (NULL);
}

void	clear_env_list(t_env_list *stack)
{
	t_env_node	*cur_node;
	t_env_node	*next_env_node;

	cur_node = stack->head;
	if (cur_node != NULL)
	{
		while (cur_node->next != NULL)
		{
			next_env_node = cur_node->next;
			free(cur_node->key);
			free(cur_node->value);
			free(cur_node);
			cur_node = next_env_node;
		}
		free(cur_node->key);
		free(cur_node->value);
		free(cur_node);
	}
	free(stack);
}

void	remove_env_node(t_env_list *stack, t_env_node *node)
{
	if (node->prev == NULL)
		stack->head = node->next;
	else
		node->prev->next = node->next;
	if (node->next == NULL)
		stack->tail = node->prev;
	else
		node->next->prev = node->prev;
	free(node->key);
	free(node->value);
	free(node);
}

t_env_node	*make_env_node(char *key, char *value)
{
	t_env_node	*new_node;

	new_node = (t_env_node *)malloc(sizeof(t_env_node));
	new_node->key = ft_strdup(key);
	if (!new_node || !new_node->key)
		exit(malloc_error());
	if (value == NULL)
		new_node->value = NULL;
	else
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			exit(malloc_error());
	}
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

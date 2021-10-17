/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_operations_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:40:33 by takuya            #+#    #+#             */
/*   Updated: 2021/10/16 22:17:13 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/dlist_operations.h"

t_env_node	*make_node(char *key, char *value)
{
	t_env_node	*new_node;

	new_node = (t_env_node *)malloc(sizeof(t_env_node));
	if (new_node == NULL)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	insert_after(t_env_list *stack, t_env_node *node, t_env_node *new_node)
{
	new_node->prev = node;
	new_node->next = node->next;
	if (node->next == NULL)
		stack->tail = new_node;
	else
		node->next->prev = new_node;
	node->next = new_node;
}

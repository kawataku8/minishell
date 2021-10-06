/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:21:26 by takuya            #+#    #+#             */
/*   Updated: 2021/10/03 16:41:56 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/dlist_operations.h"

void	insert_before(t_env_list *stack, t_env_node *node, t_env_node *new_node)
{
	new_node->prev = node->prev;
	new_node->next = node;
	if (node->prev == NULL)
		stack->head = new_node;
	else
		node->prev->next = new_node;
	node->prev = new_node;
}

void	insert_beginning(t_env_list *stack, t_env_node *new_node)
{
	if (stack->head == NULL)
	{
		stack->head = new_node;
		stack->tail = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
	}
	else
		insert_before(stack, stack->head, new_node);
}

void	insert_end(t_env_list *stack, t_env_node *new_node)
{
	if (stack->tail == NULL)
		insert_beginning(stack, new_node);
	else
		insert_after(stack, stack->tail, new_node);
}

void	clear_stack(t_env_list *stack)
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

void	remove_node(t_env_list *stack, t_env_node *node)
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

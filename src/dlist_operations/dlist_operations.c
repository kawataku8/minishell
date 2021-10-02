/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:21:26 by takuya            #+#    #+#             */
/*   Updated: 2021/10/02 13:25:11 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/dlist_operations.h"

//key,valueは事前にmallocされている前提
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

// void	print_env_list(t_env_list *stack)
// {
// 	t_env_node *node = stack->head;

// 	while(node)
// 	{
// 		printf("key:[%s],value:[%s]\n",node->key,node->value);
// 		node = node->next;
// 	}
// }

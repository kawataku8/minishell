/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:52:05 by stakabay          #+#    #+#             */
/*   Updated: 2021/10/13 23:45:30 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"

t_env_node	*merge(t_env_node *a, t_env_node *b)
{
	t_env_node	*result;
	size_t		len;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	len = ft_strlen(a->key);
	if (len <= ft_strlen(b->key))
		len = ft_strlen(b->key);
	if (ft_strncmp(a->key, b->key, len) < 0)
	{
		result = a;
		result->next = merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = merge(a, b->next);
	}
	return (result);
}

void	merge_sort_rec(t_env_node *head,
						t_env_node **frontref, t_env_node **backref)
{
	t_env_node	*slow;
	t_env_node	*fast;

	slow = head;
	fast = head->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontref = head;
	*backref = slow->next;
	slow->next = NULL;
}

void	merge_sort(t_env_node **headref)
{
	t_env_node	*head;
	t_env_node	*a;
	t_env_node	*b;

	head = *headref;
	if (head == NULL || head->next == NULL)
		return ;
	merge_sort_rec(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*headref = merge(a, b);
}

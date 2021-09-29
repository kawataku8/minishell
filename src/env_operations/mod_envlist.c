/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_envlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:57:14 by takuya            #+#    #+#             */
/*   Updated: 2021/09/28 16:57:51 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env_operations.h"
#include "../../include/cmd.h"

void	mod_envlist_value(char *target_key,
char *new_value, t_env_list *env_list)
{
	t_env_node	*cur_envnode;

	cur_envnode = env_list->head;
	while (cur_envnode != NULL)
	{
		if (my_strcmp(target_key, cur_envnode->key) == 0)
		{
			free(cur_envnode->value);
			cur_envnode->value = new_value;
			return ;
		}
		cur_envnode = cur_envnode->next;
	}
}

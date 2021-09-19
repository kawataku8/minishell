/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:50:57 by stakabay          #+#    #+#             */
/*   Updated: 2021/09/19 21:50:59 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"

int	ft_env(t_env_list *list)
{
	t_env_node	*ndptr;

	ndptr = list->head;
	while (ndptr != NULL)
	{
		if (ndptr->value && (ft_strncmp(ndptr->key, "?", 1)))
		{
			put_string_fd(ndptr->key, STD_OUT);
			put_string_fd("=", STD_OUT);
			ft_putendl_fd(ndptr->value, STD_OUT);
		}
		ndptr = ndptr->next;
	}
	return (SUCCEEDED);
}

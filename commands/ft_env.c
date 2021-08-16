/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 07:59:06 by stakabay          #+#    #+#             */
/*   Updated: 2021/08/06 18:41:39 by stakabay         ###   ########.fr       */
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

// int	main(void)
// {
// 	t_env_list	env_list;
// 	t_env_node	*ndptr;
// 	t_env_node	*node;

// 	env_list.head = NULL;
// 	env_list.tail = NULL;
// 	ndptr = make_env_node("TEST", "SUCCEEDED");
// 	insert_end(&env_list, ndptr);
// 	node = make_env_node("PWD", getenv("PWD"));
// 	insert_end(&env_list, node);
// 	node = make_env_node("OLDPWD", getenv("OLDPWD"));
// 	insert_end(&env_list, node);
// 	ft_env(&env_list);
// }

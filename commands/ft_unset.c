/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:50:48 by stakabay          #+#    #+#             */
/*   Updated: 2021/10/23 18:12:02 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command.h"

int	ft_unset(char **argv, t_env_list *list)
{
	t_env_node	*node;
	int			renum;

	renum = SUCCEEDED;
	while (*argv)
	{
		if (!is_valid_env_key(*argv))
		{
			put_string_fd("minishell: unset: \'", STD_ERR);
			put_string_fd(*argv, STD_ERR);
			ft_putendl_fd("\': not a valid identifier", STD_ERR);
			renum = ERROR;
		}
		else
		{
			node = serch_nodes(list, *argv);
			if (node)
			{
				remove_env_node(list, node);
			}
		}
		argv++;
	}
	return (renum);
}

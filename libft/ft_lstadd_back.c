/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkawahar <tkawahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:16:39 by tkawahar          #+#    #+#             */
/*   Updated: 2020/07/05 19:21:31 by tkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *current_lst;

	if (lst && new)
	{
		if (!(*lst))
			*lst = new;
		else
		{
			current_lst = ft_lstlast(*lst);
			current_lst->next = new;
		}
	}
}

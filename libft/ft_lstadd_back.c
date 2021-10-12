/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:16:39 by tkawahar          #+#    #+#             */
/*   Updated: 2021/10/12 21:54:21 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current_lst;

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

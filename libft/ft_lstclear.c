/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:37:35 by tkawahar          #+#    #+#             */
/*   Updated: 2021/10/12 22:00:40 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_lst;
	t_list	*lst_temp;

	if (lst && del)
	{
		lst_temp = *lst;
		while (lst_temp)
		{
			next_lst = lst_temp->next;
			ft_lstdelone(lst_temp, del);
			lst_temp = next_lst;
		}
		*lst = NULL;
	}
}

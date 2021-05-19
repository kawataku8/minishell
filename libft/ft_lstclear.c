/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkawahar <tkawahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:37:35 by tkawahar          #+#    #+#             */
/*   Updated: 2020/07/05 19:24:00 by tkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *next_lst;
	t_list *lst_temp;

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

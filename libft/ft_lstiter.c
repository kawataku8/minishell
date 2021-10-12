/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:29:49 by tkawahar          #+#    #+#             */
/*   Updated: 2021/10/12 22:00:49 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current_lst;

	if (!lst || !f)
		return ;
	current_lst = lst;
	while (current_lst)
	{
		f(current_lst->content);
		current_lst = current_lst->next;
	}
}

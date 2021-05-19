/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkawahar <tkawahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:29:49 by tkawahar          #+#    #+#             */
/*   Updated: 2020/07/05 19:27:25 by tkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *current_lst;

	if (!lst || !f)
		return ;
	current_lst = lst;
	while (current_lst)
	{
		f(current_lst->content);
		current_lst = current_lst->next;
	}
}

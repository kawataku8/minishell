/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:45:36 by tkawahar          #+#    #+#             */
/*   Updated: 2021/10/12 22:16:04 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_tree;

	if (!lst || !f)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	lst = lst->next;
	new_tree = new;
	while (lst)
	{
		new->next = ft_lstnew(f(lst->content));
		if (!(new->next))
		{
			ft_lstclear(&new_tree, del);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (new_tree);
}

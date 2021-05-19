/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkawahar <tkawahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:45:36 by tkawahar          #+#    #+#             */
/*   Updated: 2020/07/05 19:30:56 by tkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *new_tree;

	if (!lst || !f)
		return (NULL);
	if (!(new = ft_lstnew(f(lst->content))))
		return (NULL);
	lst = lst->next;
	new_tree = new;
	while (lst)
	{
		if (!(new->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&new_tree, del);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (new_tree);
}

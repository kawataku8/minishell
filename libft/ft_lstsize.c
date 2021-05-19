/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkawahar <tkawahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 14:43:17 by tkawahar          #+#    #+#             */
/*   Updated: 2020/07/05 19:17:20 by tkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current_lst;
	int		size;

	size = 0;
	current_lst = lst;
	while (current_lst)
	{
		current_lst = current_lst->next;
		size++;
	}
	return (size);
}

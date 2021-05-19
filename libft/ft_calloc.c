/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkawahar <tkawahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 11:21:18 by tkawahar          #+#    #+#             */
/*   Updated: 2020/07/05 13:20:26 by tkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *p;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (!(p = (void *)malloc(count * size)))
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}

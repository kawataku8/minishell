/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:46:13 by tkawahar          #+#    #+#             */
/*   Updated: 2021/10/12 22:02:16 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	ch_s1;
	unsigned char	ch_s2;

	while (n--)
	{
		ch_s1 = (unsigned char)*s1;
		ch_s2 = (unsigned char)*s2;
		if (ch_s1 != ch_s2)
			return (ch_s1 - ch_s2);
		if (ch_s1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return (0);
}

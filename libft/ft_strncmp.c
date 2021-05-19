/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkawahar <tkawahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:46:13 by tkawahar          #+#    #+#             */
/*   Updated: 2020/12/21 17:50:57 by tkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char ch_s1;
	unsigned char ch_s2;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 10:17:15 by tkawahar          #+#    #+#             */
/*   Updated: 2021/10/12 21:53:56 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	while (*haystack && (len > 0) && (len >= needle_len))
	{
		if (ft_strncmp(haystack, needle, needle_len) == 0)
			return ((char *)haystack);
		len--;
		haystack++;
	}
	return (NULL);
}

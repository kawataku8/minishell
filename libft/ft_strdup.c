/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkawahar <tkawahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 16:44:07 by tkawahar          #+#    #+#             */
/*   Updated: 2020/07/03 11:24:30 by tkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*newstr;
	size_t	s1_len;

	s1_len = ft_strlen(s1) + 1;
	if (!(newstr = (char *)malloc(sizeof(char) * s1_len)))
		return (NULL);
	(void)ft_memcpy(newstr, s1, s1_len);
	return (newstr);
}

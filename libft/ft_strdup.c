/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 16:44:07 by tkawahar          #+#    #+#             */
/*   Updated: 2021/10/12 22:31:53 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*newstr;
	size_t	s1_len;

	s1_len = ft_strlen(s1) + 1;
	newstr = (char *)malloc(sizeof(char) * s1_len);
	if (!newstr)
		return (NULL);
	(void)ft_memcpy(newstr, s1, s1_len);
	return (newstr);
}

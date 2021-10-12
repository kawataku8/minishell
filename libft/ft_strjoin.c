/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:36:52 by tkawahar          #+#    #+#             */
/*   Updated: 2021/10/12 22:13:20 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *s1, const char *s2)
{
	char	*s;

	s = s1;
	while (*s)
		s++;
	while ((*s2 != '\0'))
		*s++ = *s2++;
	*s = '\0';
	return (s1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = malloc(sizeof(char) * len);
	if (!newstr)
		return (0);
	*newstr = '\0';
	(void)ft_strcpy(newstr, s1);
	(void)ft_strcpy(newstr, s2);
	return (newstr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkawahar <tkawahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 12:54:15 by tkawahar          #+#    #+#             */
/*   Updated: 2020/07/05 12:57:51 by tkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*found;
	char	*current_position;
	char	ch;

	ch = (char)c;
	found = NULL;
	if (ch == '\0')
		return (ft_strchr(s, '\0'));
	while ((current_position = ft_strchr(s, ch)) != 0)
	{
		found = current_position;
		s = current_position + 1;
	}
	return (found);
}

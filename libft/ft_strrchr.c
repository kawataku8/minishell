/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 12:54:15 by tkawahar          #+#    #+#             */
/*   Updated: 2021/10/12 22:20:21 by takuya           ###   ########.fr       */
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
	while (1)
	{
		current_position = ft_strchr(s, ch);
		if (current_position == 0)
			break ;
		found = current_position;
		s = current_position + 1;
	}
	return (found);
}

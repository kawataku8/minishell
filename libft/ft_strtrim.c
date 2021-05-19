/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkawahar <tkawahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:06:52 by tkawahar          #+#    #+#             */
/*   Updated: 2020/07/03 11:24:30 by tkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_front_index(char const *s1, char const *set)
{
	int index;
	int set_index;
	int set_there;

	index = 0;
	while (s1[index])
	{
		set_index = 0;
		set_there = 0;
		while (set[set_index])
		{
			if (s1[index] == set[set_index])
			{
				set_there++;
				break ;
			}
			set_index++;
		}
		if (set_there == 0)
			break ;
		index++;
	}
	return (index);
}

static int	ft_get_end_index(char const *s1, char const *set, int end_index)
{
	int set_index;
	int set_there;

	while (end_index >= 0)
	{
		set_index = 0;
		set_there = 0;
		while (set[set_index])
		{
			if (s1[end_index] == set[set_index])
			{
				set_there++;
				break ;
			}
			set_index++;
		}
		if (set_there == 0)
			break ;
		end_index--;
	}
	return (end_index);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		front_index;
	int		end_index;
	char	*trimed_str;

	if (s1 == NULL)
		return (NULL);
	end_index = 0;
	while (s1[end_index])
		end_index++;
	front_index = ft_get_front_index(s1, set);
	end_index = ft_get_end_index(s1, set, end_index - 1);
	if (end_index == -1)
	{
		if (!(trimed_str = (char *)malloc(sizeof(char))))
			return (NULL);
		*trimed_str = '\0';
		return (trimed_str);
	}
	if (!(trimed_str =
	(char *)malloc(sizeof(char) * (end_index - front_index + 2))))
		return (NULL);
	(void)ft_strlcpy(trimed_str, s1 + front_index, end_index - front_index + 2);
	return (trimed_str);
}

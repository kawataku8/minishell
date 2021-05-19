/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkawahar <tkawahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 11:21:05 by tkawahar          #+#    #+#             */
/*   Updated: 2020/07/05 13:54:27 by tkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' ||
	c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

int			ft_atoi(char *str)
{
	int			sign;
	long long	result;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		str++;
		sign *= -1;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if ((result * 10) + (*str - '0') < result)
			return (sign > 0 ? -1 : 0);
		result = (result * 10) + (*str - '0');
		str++;
	}
	return ((int)(result * sign));
}

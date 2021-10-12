/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 11:21:05 by tkawahar          #+#    #+#             */
/*   Updated: 2021/10/12 23:01:13 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v')
		return (1);
	else if (c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

char	*manage_minus(int *sign, char *str)
{
	if (*str == '-')
	{
		str++;
		*sign *= -1;
	}
	else if (*str == '+')
		str++;
	return (str);
}

int	ft_atoi(char *str)
{
	int			sign;
	long long	result;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	str = manage_minus(&sign, str);
	while (*str >= '0' && *str <= '9')
	{
		if ((result * 10) + (*str - '0') < result)
		{
			if (sign > 0)
				return (-1);
			else
				return (0);
		}
		result = (result * 10) + (*str - '0');
		str++;
	}
	return ((int)(result * sign));
}

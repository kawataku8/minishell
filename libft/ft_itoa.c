/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 21:24:42 by tkawahar          #+#    #+#             */
/*   Updated: 2021/10/12 22:18:13 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_len(const int n)
{
	int	len;
	int	temp_n;
	int	is_minus;

	len = 0;
	temp_n = n;
	is_minus = 0;
	if (temp_n < 0)
	{
		len++;
		temp_n *= -1;
		is_minus++;
	}
	while (temp_n > 0)
	{
		len++;
		temp_n /= 10;
	}
	return (len);
}

static char	*ft_make_zero(size_t size)
{
	char	*p;

	p = (char *)malloc(size * 2);
	if (!p)
		return (NULL);
	p[0] = '0';
	p[1] = '\0';
	return (p);
}

static char	*ft_make_num_str(char *dst, int n, int len)
{
	dst[len] = '\0';
	len--;
	while (n > 0)
	{
		dst[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (dst);
}

char	*ft_itoa(int n)
{
	char	*n_str;
	int		len;
	int		is_minus;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	is_minus = 0;
	len = ft_num_len(n);
	if (n == 0)
	{
		n_str = ft_make_zero(sizeof(char));
		return (n_str);
	}
	if (n < 0)
	{
		is_minus++;
		n *= -1;
	}
	n_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(n_str))
		return (NULL);
	n_str = ft_make_num_str(n_str, n, len);
	if (is_minus)
		n_str[0] = '-';
	return (n_str);
}

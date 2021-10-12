/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 17:21:58 by tkawahar          #+#    #+#             */
/*   Updated: 2021/10/12 23:05:56 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_num_words(char const *s, char c)
{
	int	i;
	int	num_of_words;

	i = 0;
	num_of_words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			num_of_words++;
		}
		if (!s[i])
			break ;
		i++;
	}
	return (num_of_words);
}

static void	*ft_memfree(char **words, int index)
{
	while (index--)
		free(words[index]);
	free(words);
	return (NULL);
}

static	char	**ft_getword(char **words, char const *s,
char c, int num_of_words)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	index = 0;
	while (num_of_words > index && s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[j] != c && s[j])
			j++;
		words[index] = (char *)malloc(sizeof(char) * (j - i + 1));
		if (!(words[index]))
			return (ft_memfree(words, index));
		(void)ft_strlcpy(words[index], (s + i), (j - i + 1));
		i = j;
		index++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	char	**result;
	int		num_of_words;

	if (s == NULL)
		return (NULL);
	num_of_words = ft_get_num_words(s, c);
	words = (char **)malloc(sizeof(char *) * (num_of_words + 1));
	if (!(words))
		return (NULL);
	result = words;
	words = ft_getword(words, s, c, num_of_words);
	if (!(words))
		return (NULL);
	words[num_of_words] = NULL;
	return (result);
}

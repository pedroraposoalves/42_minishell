/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:36:26 by pemirand          #+#    #+#             */
/*   Updated: 2024/10/29 16:34:37 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_word_len(char const *s, char sep)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == sep)
			return (i);
		i++;
	}
	return (i);
}

static int	ft_count_words(char const *s, char sep)
{
	int		n_words;
	int		i;
	int		len;

	if (!s)
		return (0);
	n_words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		len = ft_word_len(&s[i], sep);
		if (len > 0)
			n_words++;
		i += len;
	}
	return (n_words);
}

static int	ft_add_word(char **str_split, const char *str, int index, int len)
{
	int		i;

	str_split[index] = ft_substr(str, 0, len);
	if (!str_split[index])
	{
		i = 0;
		while (i <= index)
		{
			free(str_split[i]);
			i++;
		}
		free(str_split);
		return (-1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	char	**res;

	if (!s)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		len = ft_word_len(s, c);
		if (len > 0)
		{
			if (ft_add_word(res, s, i++, len) == -1)
				return (NULL);
		}
		s += len;
	}
	res[i] = 0;
	return (res);
}

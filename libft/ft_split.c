/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:29:31 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/30 14:52:53 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Funcao que conta e retorna a quantidade de palavras na string*/

static int	count_words(char const *s, char c)
{
	int	word;
	int	i;

	word = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c) && ((s[i + 1] == c) || (s[i + 1] == '\0')))
			word++;
		i++;
	}
	return (word);
}

/* Funcao que aloca tamanho da palavra e copia a palavra 
para uma nova substring */

static char	*put_word(char const *s, char c)
{
	char	*str;
	int		i;
	int		len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*Funcao que chama a funcao put_word e faz o free se a alocacao falhar. */

static char	*ft_cpy_str(int i, char const *s, char c, char **res)
{
	res[i] = put_word(s, c);
	if (!res[i])
	{
		while (i > 0)
		{
			i--;
			free(res[i]);
		}
		free(res);
		return (NULL);
	}
	return (res[i]);
}

char	**ft_split(char const *s, char c)
{
	int		nb_words;
	int		i;
	char	**res;

	if (!s)
		return (NULL);
	i = 0;
	nb_words = count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!res)
		return (NULL);
	while (i < nb_words)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			res[i] = ft_cpy_str(i, s, c, res);
		if (!res || res[i] == NULL)
			return (NULL);
		while (*s && *s != c)
			s++;
		i++;
	}
	res[i] = 0;
	return (res);
}
/*
int main(void)
{
    char    a1[] = "a b c de f";
    char    **teste;

    teste = ft_split(a1, ' ');
    
    puts(*(teste));
    puts(*(teste + 1));
    puts(*(teste + 2));
    puts(*(teste + 3));
    puts(*(teste + 4));
    
    return 0;
}*/

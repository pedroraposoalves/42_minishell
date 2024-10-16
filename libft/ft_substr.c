/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:44 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/20 12:18:32 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Funcao que cria uma substring a partir de uma string e 
retorna um ponteiro para a mesma. */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ret;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(&s[start]);
	if (!s)
		return (NULL);
	ret = (char *)malloc(sizeof(*s) * (len + 1));
	if (!ret)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
			ret[j++] = s[i];
		i++;
	}
	ret[j] = 0;
	return (ret);
}
/* 
int main(void)
{
    //char a1[] = "teste";

    printf("\n%p\n\n", ft_substr("hola", 654564, 0));
    return 0;
} */

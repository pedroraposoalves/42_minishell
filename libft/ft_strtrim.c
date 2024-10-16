/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:19:59 by malves-b          #+#    #+#             */
/*   Updated: 2023/11/02 15:09:53 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Funcao que verifica em uma string, se o caracter passado como
segundo parametro existe no inicio e no final da string e retorna
a string sem os caracters encontrados*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		i;
	int		f;

	ret = NULL;
	if (!s1 || !set)
		return (NULL);
	if (s1 != 0 && set != 0)
	{
		i = 0;
		f = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[f - 1] && ft_strchr(set, s1[f - 1]) && f > i)
			f--;
		ret = (char *)malloc(sizeof(char) * (f - i + 1));
		if (ret)
			ft_strlcpy(ret, &s1[i], f - i + 1);
	}
	return (ret);
}
/* 
int main(void)
{
    puts(ft_strtrim("!!-!AmigoA!", "!"));
    return 0;
} */

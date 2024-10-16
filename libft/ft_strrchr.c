/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:28:22 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/19 15:08:51 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Funcao que encontra a ultima ocorrencia do caractere passado como
parametro em uma string. Funcao retorna um ponteiro para o mesmo. */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if ((char)c == 0)
		return ((char *)s + i);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
/* 
int main(void)
{
    char a1[] = "exercise 01";
    
    printf("%s\n", ft_strrchr(a1, 'x'));
    printf("%s\n", strrchr(a1, 'x'));
    return 0;
} */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:00:26 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/13 12:09:51 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Funcao que encontra um caractere semelhante em uma string
e imprime a string a partir do caractere encontrado
Funcao tambem recebe um parametro ate que posicao se deve encontrar */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	x;
	size_t			i;

	str = (unsigned char *)s;
	x = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[0] == x)
			return (str);
		str++;
		i++;
	}
	return (NULL);
}
/* 
int main(void)
{
    char a1[] = "teste 0123";
    
    puts(ft_memchr(a1, '0', 8));
    puts(memchr(a1, '0', 8));
    return 0;
} */

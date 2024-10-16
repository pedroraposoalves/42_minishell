/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:47:53 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/19 14:52:03 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Funcao que verifica o espaco vazio de uma string (dst)
e preenche com o (src). Funcao retorna o tamanho do
src + a quantidade de casas ja preenchidas */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	char	*a;

	a = (char *)src;
	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	while (a[j] && (i + j + 1) < size)
	{
		dst[i + j] = a[j];
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (i + ft_strlen(a));
}

//#include <bsd/string.h>
/*
#include <stdio.h>
//compilar funcao original com "lbsd" no final

int main(void)
{
    char dest[4] = "oi";
    char src[] = "teste";
    
    puts(dest);
    printf("%zu\n", ft_strlcat(dest, src, 4));
    puts(dest);
    
    return 0;
} */

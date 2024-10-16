/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:03:58 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/10 14:49:50 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Funcao que copia o valor de uma string 
para outra e retorna o tamanho da source
*/

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen((char *)src));
	while (src[i] != '\0' && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen((char *)src));
}
/* 
int main(void)
{
    char a1[] = "teste";
    char a2[] = "matheus";

    printf("%ld\n", ft_strlcpy(a1, a2, 4));
    puts(a1);
    
    return 0;
} */
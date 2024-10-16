/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:13:05 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/20 14:28:11 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Funcao que verifica um caractere em uma string e retorna 
um ponteiro para o caracter encontrado.
Se a string nao possuir o caracter passado como parametro
a funcao retorna um ponteiro para NULL*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while ((*s != (char)c) && (*s != '\0'))
	{
		s++;
	}
	if (*s == (char)c)
	{
		return ((char *)s);
	}
	return ((char *) NULL);
}
/*
int main(void)
{
    char a1[] = "0x55aec840b020";
    
    printf("%s\n", ft_strchr(a1, 'c'));
    printf("%s\n", strchr(a1, 'c'));
    return 0;
}*/
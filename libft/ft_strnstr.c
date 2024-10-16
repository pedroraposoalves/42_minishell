/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:57:52 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/16 17:43:07 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Funcao que procura uma substring dentro de uma string e retorna
a partir da substring encontrada. Funcao recebe um limitador
que delimita a posicao limite de procura. */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	t;

	i = 0;
	if (little[0] == '\0' || little == NULL)
		return ((char *)big);
	if (big[0] == '\0' || !big)
	{
		return (NULL);
	}
	while (big[i] != '\0' && i < len)
	{
		t = 0;
		while (big[i + t] && little[t]
			&& i + t < len && big[i + t] == little[t])
			t++;
		if (!little[t])
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
/* 
int main(void)
{
    const char a1[] = "teste 01";
    const char a2[] = "xx";

    puts(ft_strnstr(a1, a2, 9));
} */

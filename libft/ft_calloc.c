/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:54:35 by malves-b          #+#    #+#             */
/*   Updated: 2024/09/08 16:21:30 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Funcao que aloca espaco de memoria para um bloco de dados
Na funcao calloc os lixos de memoria sao deletados, ou seja,
inicializa com '0' */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t n, size_t size)
{
	void	*x;

	if (n == 0 || size == 0)
		return (malloc(0));
	if (n > ((size_t) -1) / size)
	{
		return (NULL);
	}
	x = malloc(n * size);
	if (!x)
		return (NULL);
	ft_bzero(x, n * size);
	return (x);
}
/* 
int main(void)
{
    int *a1;
    int i;

    a1 = (int *) ft_calloc(sizeof(int), 4);
    i = 0;
    while (i < sizeof(a1))
    {
        printf("%i\n", *a1);
        i++;
    }
    printf("%lu", sizeof(int));
    return 0;
} */

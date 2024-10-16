/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:45:04 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/16 18:21:39 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Funcao que converte uma string em um inteiro */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	r;
	int	sinal;

	sinal = 1;
	i = 0;
	r = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sinal *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r *= 10;
		r += (nptr[i] - '0');
		i++;
	}
	r *= sinal;
	return (r);
}
/*
int main(void)
{
    char a1[] = "\n 10";

    printf("%i\n", ft_atoi(a1));
    return 0;
}*/

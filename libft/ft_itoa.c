/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:23:36 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/21 15:33:16 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Funcao que converte um integer em uma string*/

#include "libft.h"

static unsigned int	size_number(int number)
{
	unsigned int	x;

	x = 0;
	if (number == 0)
		return (1);
	if (number < 0)
		x += 1;
	while (number != 0)
	{
		number /= 10;
		x++;
	}
	return (x);
}

char	*ft_itoa(int n)
{
	char			*ret;
	unsigned int	y;
	unsigned int	x;

	y = size_number(n);
	ret = (char *)malloc(sizeof(char) * (y + 1));
	if (ret == NULL)
		return (NULL);
	if (n < 0)
	{
		ret[0] = '-';
		x = -n;
	}
	else
		x = n;
	if (x == 0)
		ret[0] = '0';
	ret[y] = '\0';
	while (x != 0)
	{
		ret[y - 1] = (x % 10) + '0';
		x /= 10;
		y--;
	}
	return (ret);
}
/* 
int main(int argc, char const *argv[])
{
    (void)argc;

    printf("%s", argv[1]);
} */

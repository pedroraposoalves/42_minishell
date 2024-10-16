/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:05:36 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/16 14:48:54 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Funcao que conta e retorna do tamanho de uma string

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
/* 
#include <stdio.h>

int	main(void)
{
	printf("%i", ft_strlen("jaca mole"));
} */

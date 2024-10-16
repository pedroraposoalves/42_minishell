/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 09:27:43 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/11 09:45:09 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Funcao que converte um caracter menusculo em maiusculo

#include "libft.h"

int	ft_toupper(int a)
{
	if (a >= 'a' && a <= 'z')
		return (a - 32);
	return (a);
}
/* 
#include <ctype.h>

int main(void)
{
    printf("After %c\n", toupper('l'));
    printf("After %c\n", ft_toupper('l'));
    return 0;
} */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 09:45:52 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/11 10:06:01 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Funcao que converte um caracter maiusculo em menusculo

#include "libft.h"

int	ft_tolower(int a)
{
	if (a >= 'A' && a <= 'Z')
		return (a + 32);
	return (a);
}
/* 
#include <ctype.h>

int main(void)
{
    printf("After %c\n", tolower('A'));
    printf("After %c\n", ft_tolower('A'));
    return 0;
} */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:52:07 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/03 15:53:06 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int i)
{
	if (('a' <= i && i <= 'z') || ('A' <= i && i <= 'Z'))
		return (1024);
	return (0);
}
/* 
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("%i \n", ft_isalpha('J'));
	printf("%i", isalpha('a'));
} */

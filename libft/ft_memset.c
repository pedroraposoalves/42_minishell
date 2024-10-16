/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:22:45 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/09 15:14:57 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*p;

	p = (char *)b;
	while (len > 0)
	{
		p[len - 1] = c;
		len--;
	}
	return (b);
}
/* 
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char a[40] = "teste 01";

	puts(memset(a, '!', 40));
	puts(ft_memset(a, '@', 50));
}
 */
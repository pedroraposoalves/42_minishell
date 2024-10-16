/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:06:03 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/16 14:45:35 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*a;
	const unsigned char	*b;
	size_t				i;

	a = (const unsigned char *)s1;
	b = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	return (0);
}
/* 
int main(void)
{
    char a1[] = "\xff\xaa\xde\xffMACOSX\xff";
    char a2[] = "\xff\xaa\xde\x02";

    printf("%i\n", memcmp(a1, a2, 8));
    printf("%i\n", ft_memcmp(a1, a2, 8));
    return 0;
} */

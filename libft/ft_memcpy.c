/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:01:24 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/11 17:25:00 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *a, const void *b, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)a;
	s = (char *)b;
	if (a == b)
		return (a);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (a);
}
/*
int main(void)
{
    char a[] = "empty";
    char b[28] = "empty";

    puts(b);
    ft_memcpy(b, a, 0);
    puts(b);
}*/
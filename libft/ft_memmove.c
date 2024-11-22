/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:36:26 by pemirand          #+#    #+#             */
/*   Updated: 2024/10/29 16:34:50 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*ps;
	char		*pd;
	size_t		i;

	if (!dest && !src)
		return (dest);
	ps = (char *) src;
	pd = (char *) dest;
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			pd[i] = ps[i];
			i++;
		}
	}
	else
	{
		while (n--)
			pd[n] = ps[n];
	}
	return (dest);
}

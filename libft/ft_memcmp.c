/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:36:26 by pemirand          #+#    #+#             */
/*   Updated: 2024/10/29 16:34:54 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_type;
	unsigned char	*s2_type;

	s1_type = (unsigned char *) s1;
	s2_type = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (s1_type[i] != s2_type[i])
			return (s1_type[i] - s2_type[i]);
		i++;
	}
	return (0);
}

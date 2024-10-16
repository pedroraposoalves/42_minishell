/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:54:45 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/09 11:20:39 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int i)
{
	if (i >= 32 && i <= 126)
		return (16384);
	return (0);
}
/*

#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	printf("%i\n", ft_isprint(31));
	printf("%i", isprint(31));
}*/

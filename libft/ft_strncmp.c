/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:18:38 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/13 10:26:12 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Funcao que compara duas strings ate o numero de caracteres 
passado como parametro. */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (((s1[i] && s2[i]) != '\0') && i < n - 1)
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (((unsigned char)s1[i] - (unsigned char)s2[i]));
}
/* 
int main(void)
{
    char a1[] = "teste 04";
    char a2[] = "teste 06";
    
    printf("%i\n", ft_strncmp(a1, a2, 8));
    printf("%i\n", strncmp(a1, a2, 8));
} */
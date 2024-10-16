/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:03:43 by malves-b          #+#    #+#             */
/*   Updated: 2023/11/02 15:03:23 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Funcao que cria uma nova string com base na string 's' passada
como primeiro parametro, com a alteracao da funcao de
callback passada como segundo parametro */

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ret;

	i = 0;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s)) + 1);
	if (ret == NULL)
		return (NULL);
	while (s[i])
	{
		ret[i] = f(i, s[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
/* 
static aux(unsigned int, char str)
{
    
}

int main(void)
{
    
    return 0;
} */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:02:28 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/20 12:16:22 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Funcao que concatena duas strings e retorna um ponteiro
para a string criada*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*ret;

	i = 0;
	j = 0;
	ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}
/* 
int main(void)
{
    char    *ex;

    ex = ft_strjoin("bom", "dia");
    puts(ex);
    return 0;
} */

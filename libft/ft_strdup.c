/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:56:44 by malves-b          #+#    #+#             */
/*   Updated: 2023/10/19 13:57:04 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Funcao que cria uma copia de uma string
e retorna o endereco do ponteiro criado*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*a;
	int		i;

	i = 0;
	a = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (a == NULL)
		return (NULL);
	while (s[i])
	{
		a[i] = s[i];
		i++;
	}
	a[i] = 0;
	return (a);
}
/* 
int main(void)
{
	const char a1[] = "teste 01";
	const char *a2;
	int		i;

	printf("%p\n", &a1);


	a2 = ft_strdup(a1);
	while (i < sizeof(a2))
	{
		printf("Endereco: %p | armazena: %c\n", a2, *(a2 + i));
		i++;
	}
	return 0;
} */

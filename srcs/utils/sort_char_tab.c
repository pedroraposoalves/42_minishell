/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_char_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:25:41 by pemirand          #+#    #+#             */
/*   Updated: 2024/11/22 13:27:51 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_swap(char **a, int i, int j)
{
	char	*temp;

	temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		if (s1[i] < s2[i] || s1[i] > s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}

char	**ft_sort_char_tab(char **tab, int size)
{
	int	i;
	int	j;
	int	j_min;

	i = 1;
	while (i < (size - 1))
	{
		j_min = i;
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(tab[j_min], tab[j]) > 0)
				j_min = j;
			j++;
		}
		if (j_min != i)
		{
			ft_swap(tab, i, j_min);
		}
		i++;
	}
	return (tab);
}

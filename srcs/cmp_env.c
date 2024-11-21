/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:48:50 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/12 17:23:02 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmp_env(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != '=')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

void	remove_badenvp(char **str, int i, int j)
{
	char	*new_str;
	int		word_len;
	int		index;

	word_len = 1;
	while ((*str)[j] != 32 && (*str)[j] != '"' && (*str)[j++])
		word_len++;
	while ((*str)[j])
		j++;
	new_str = malloc((j + 1) - word_len);
	j = 0;
	index = 0;
	while ((*str)[j])
	{
		if (index == i)
			index += (word_len - 1);
		if ((*str)[index] == '\0')
			break ;
		new_str[j++] = (*str)[index++];
	}
	new_str[j] = '\0';
	free ((*str));
	(*str) = new_str;
}

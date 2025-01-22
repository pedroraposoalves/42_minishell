/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:48:50 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/22 12:19:48 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (s2[i] && ft_isalnum(s2[i]))
		return (0);
	return (i);
}

char	*remove_badenvp(char **str, int j)
{
	char	new_str[900];
	int		index;

	if ((*str)[0] != '\"' && j < 1 && !ft_strchr(str[0], '.')
		&& !ft_strchr(str[0], '=') && !ft_strchr(str[0], '/'))
	{
		free((*str));
		return (ft_strdup(""));
	}
	index = -1;
	while (++index < j)
		new_str[index] = (*str)[index];
	while ((*str)[j] != 32 && (*str)[j] != '.' && (*str)[j] != '"' && (*str)[j]
		!= '=' && (*str)[j] != '/' && (*str)[j])
		j++;
	while ((*str)[j])
	{
		new_str[index] = (*str)[j++];
		index++;
	}
	new_str[index] = '\0';
	free ((*str));
	return (ft_strdup(new_str));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:17:40 by malves-b          #+#    #+#             */
/*   Updated: 2024/10/29 16:43:47 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Add a word in the (char **) */
char	**add_word(char **args, char *new_word)
{
	char	**new_args;
	int		i;

	i = 0;
	while (args[i])
		i++;
	new_args = ft_calloc(sizeof(char *), i + 2);
	if (!new_args)
		return (NULL);
	i = -1;
	while (args[++i])
	{
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
		{
			free_double_array(new_args);
			return (NULL);
		}
	}
	new_args[i++] = ft_strdup(new_word);
	new_args[i] = NULL;
	if (args)
		free_double_array(args);
	return (new_args);
}

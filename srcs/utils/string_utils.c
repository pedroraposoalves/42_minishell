/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:42:16 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/20 17:41:41 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_str_char(char *s, char c)
{
	int	position;

	position = 0;
	if (!s)
		return (-1);
	while (s[position] != c && s[position] != '\0')
		position++;
	return (position);
}

int	ft_specialcharpos_export(char *s)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		if ((s[i] >= 33 && s[i] <= 35) || (s[i] >= 37 && s[i] <= 47)
			|| (s[i] >= 58 && s[i] <= 60) \
			|| (s[i] >= 61 && s[i] <= 64) || (s[i] >= 91 && s[i] <= 94) \
			|| s[i] == 96 || (s[i] >= 123 && s[i] <= 126))
			return (i);
		i++;
	}
	return (-1);
}

t_main	*get_pgr(t_main *main_struct)
{
	static t_main	*pgr = NULL;

	if (main_struct)
		pgr = main_struct;
	return (pgr);
}

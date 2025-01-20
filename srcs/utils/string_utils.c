/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:42:16 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/20 12:24:59 by malves-b         ###   ########.fr       */
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

t_main	*get_pgr(t_main *main_struct)
{
	static t_main	*pgr = NULL;

	if (main_struct)
		pgr = main_struct;
	return (pgr);
}

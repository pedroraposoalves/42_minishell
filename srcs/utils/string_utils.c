/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:42:16 by pemirand          #+#    #+#             */
/*   Updated: 2024/11/22 15:44:53 by pemirand         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:16:06 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/21 22:55:14 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** @brief Function check if a special caracter is followed by
 * other special caracter
 */
int	check_isjoin(char *cmd, int *error)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (is_special_char(cmd[i]) && cmd[i] != '|')
		{
			i++;
			if ((cmd[i] == '>' || cmd[i] == '<') && cmd[i] == cmd[i - 1])
				i++;
			while (ft_isspace(cmd[i]))
				i++;
			if (is_special_char(cmd[i]))
			{
				(*error) = 2;
				print_err("minishel: syntax error near unexpected token `");
				write (2, &cmd[i], 1);
				print_err("'\n");
				return (2);
			}
		}
		i++;
	}
	return (0);
}

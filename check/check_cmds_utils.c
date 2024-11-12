/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:16:06 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/11 15:07:53 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
				printf ("minishel: syntax error near unexpected token `%c'\n",
					cmd[i]);
				return (2);
			}
		}
		i++;
	}
	return (0);
}

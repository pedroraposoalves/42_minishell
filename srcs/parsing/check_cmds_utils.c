/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:29:39 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/06 12:20:39 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_dir_after_redir(const char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			i++;
			if (cmd[i] == '>' || cmd[i] == '<')
				i++;
			while (cmd[i] == 32)
				i++;
			if (!cmd[i])
			{
				print_error(SHELL_NAME, \
					"syntax error near unexpected token `newline", NULL, NULL);
				return (2);
			}
			if (!ft_isalnum(cmd[i]))
				return (2);
		}
		i++;
	}
	return (0);
}

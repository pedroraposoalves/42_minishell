/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:29:39 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/22 13:01:59 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** @brief check if the directory is after the redir
 * @param cmd to verify
 * @return 0 if the directory is after the redir, 2 otherwise*/
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
			while (cmd[i] == 32 || cmd[i] == 34 || cmd[i] == 36 || cmd[i] == 39)
				i++;
			if (!cmd[i])
			{
				print_error(SHELL_NAME, \
					NULL, NULL, "syntax error near unexpected token `newline");
				return (2);
			}
			if (!ft_isalnum(cmd[i]))
				return (2);
		}
		i++;
	}
	return (0);
}

int	check_or_operator(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			i++;
			if (cmd[i] == '|')
				return (print_error(SHELL_NAME, NULL, NULL, \
					"invalid operator"), 100);
			while (cmd[i] == 32)
				i++;
			if (cmd[i] == '|')
				return (print_error(SHELL_NAME, NULL, NULL, \
				"syntax error near unexpected token `|'"), 2);
		}
		if (cmd[i])
			i++;
	}
	return (0);
}

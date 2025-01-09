/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:29:41 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/09 12:18:13 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** @brief check if the cmd init with a pipe
 * @param cmd to verify
 * @param error to save error
 * @return 1 if cmd init with pipe and 0 otherwise*/
int	check_init_pipe(char *cmd, int *error)
{
	int	i;

	i = 0;
	while (ft_isspace(cmd[i]))
		i++;
	if (cmd[i] == '|')
	{
		print_error(SHELL_NAME, "syntax error near unexpected token `|'", \
			cmd, NULL);
		(*error) = 2;
		return (1);
	}
	return (0);
}

/**
 * @brief check if have a command have ; or \ or more than two (> or <),
 * @param cmd command to verify
 * @return 3 if find ; or \, 2 if find more than two (> or <), 0 otherwise */
int	finderr_aux(char *cmd)
{
	if (cmd[0] == ';' || cmd[0] == '\\')
		return (print_error(SHELL_NAME, "syntax error unexpected token", \
			cmd, NULL), 3);
	if (cmd[0] && (cmd[0] == '>' || cmd[0] == '<'))
		if (cmd[1] == cmd[0] && cmd[2] == cmd[0])
			return (print_error(SHELL_NAME, "error unexpected token", \
				cmd, NULL), 2);
	return (0);
}

/** @brief check if have a command after pipe */
int	find_exe(char *cmd, int *i, int *error)
{
	int	j;

	j = *i + 1;
	while (cmd[j])
	{
		while (ft_isspace(cmd[j]))
			j++;
		if (cmd[j] == '|' || !cmd[j])
		{
			print_error(SHELL_NAME, "syntax error near unexpected token `|'", \
				NULL, NULL);
			(*error) = 2;
			return (1);
		}
		else
			break ;
	}
	if (j - *i == 1)
	{
		print_error(SHELL_NAME, \
			"syntax error near unexpected token `|'", NULL, NULL);
		(*error) = 2;
		return (1);
	}
	return (0);
}

/**
 * @brief Check if the quote is open
 * @param cmd Command to verify
 * @param i First quote position
 * @param error Var to update if quote opened
 * @return 1 if quote open and 0 if not open */
int	is_quote_open(char *cmd, int *i, int *error)
{
	int	j;

	j = *i + 1;
	while (cmd[j])
	{
		if (cmd[j] == cmd[*i])
		{
			(*i) = j;
			return (0);
		}
		j++;
	}
	print_error(SHELL_NAME, "syntax error - the quote is open", NULL, NULL);
	(*error) = 1;
	return (1);
}

/** @brief check if the cmd has open quotes,
 * any sintax error, if starts with a pipe or two followed special characters or if a directory is defined after a redir
 * @param cmd to verify
 * @return 0 if command is ok, */
int	check_cmds(char *cmd)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			is_quote_open(cmd, &i, &error);
		else if (cmd[i] == '\\' || cmd[i] == ';')
		{
			print_error(SHELL_NAME, "syntax error", NULL, NULL);
			error = 1;
		}
		else if (finderr_aux(cmd + i))
			error = 2;
		if (error || check_init_pipe(cmd, &error) || check_isjoin(cmd, &error))
			return (error);
		i++;
	}
	if (check_dir_after_redir(cmd))
		return (2);
	return (error);
}

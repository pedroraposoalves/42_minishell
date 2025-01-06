/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:16:06 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/06 12:29:10 by pemirand         ###   ########.fr       */
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
				return (print_error(SHELL_NAME, \
					"syntax error near unexpected token `", \
					cmd, NULL), 2);
			}
		}
		i++;
	}
	return (0);
}

/** @brief check if the char is a special caracter*/
int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|' || c == '&');
}

/** @brief check if is a space or white space */
int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r');
}

int	special_or_space(char *cmd, int *i, int *amount)
{
	if (ft_isspace(cmd[*i]))
	{
		while (ft_isspace(cmd[*i]))
			(*i)++;
		(*amount)++;
	}
	else if (is_special_char(cmd[*i]))
	{
		if (cmd[*i] == '>' || cmd[*i] == '<' || cmd[*i] == '&')
		{
			if (cmd[*i] == cmd[*i + 1])
			{
				(*i) += 2;
				(*amount)++;
				return (0);
			}
		}
		(*amount)++;
		(*i)++;
	}
	return (0);
}

int	is_quote(char *cmd, int *i, int *amount)
{
	if (cmd[*i] == '"')
	{
		(*i)++;
		while (cmd[*i] && cmd[*i] != '"')
			(*i)++;
		if (!cmd[*i])
			return (1);
		(*amount)++;
	}
	else if (cmd[*i] == '\'')
	{
		(*i)++;
		while (cmd[*i] && cmd[*i] != '\'')
			(*i)++;
		if (!cmd[*i])
			return (1);
		(*amount)++;
	}
	return (0);
}

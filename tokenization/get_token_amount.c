/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_amount.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:13:31 by malves-b          #+#    #+#             */
/*   Updated: 2024/10/15 14:55:23 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int	in_quote;

	in_quote = 1;
	if (cmd[*i] == '"')
	{
		(*i)++;
		while (cmd[*i] && cmd[*i] != '"')
			(*i)++;
		if (!cmd[*i])
			return (1);
		in_quote = 0;
		(*amount)++;
	}
	else if (cmd[*i] == '\'')
	{
		(*i)++;
		while (cmd[*i] && cmd[*i] != '\'')
			(*i)++;
		if (!cmd[*i])
			return (1);
		in_quote = 0;
		(*amount)++;
	}
	return (0);
}

/** @brief Get the amount of tokens of the command*/
int	get_token_amount(char *cmd)
{
	int	i;
	int	amount;

	i = 0;
	amount = 0;
	while (cmd[i])
	{
		special_or_space(cmd, &i, &amount);
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			if (is_quote(cmd, &i, &amount))
				return (1);
			i++;
		}
		else if (cmd[i] && !is_special_char(cmd[i]) && !isspace(cmd[i]))
		{
			while (cmd[i] && !is_special_char(cmd[i]) && !isspace(cmd[i])
				&& (cmd[i] != '"' && cmd[i] != '\''))
				i++;
			amount++;
		}
	}
	return (amount);
}

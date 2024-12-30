/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:13:31 by malves-b          #+#    #+#             */
/*   Updated: 2024/12/10 10:24:00 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*token_space(char *cmd, int *i)
{
	char	*token;

	token = ft_calloc(sizeof(char), 2);
	token[0] = cmd[*i];
	token[1] = '\0';
	while (ft_isspace(cmd[*i]) && cmd[*i])
		(*i)++;
	return (token);
}

char	*token_cmd(char *cmd, int *i)
{
	char	str[7000];
	int		j;

	j = 0;
	while (!ft_isspace(cmd[*i]) && !is_special_char(cmd[*i]) && cmd[*i]
		&& (cmd[*i] != '"' && cmd[*i] != '\''))
	{
		str[j++] = cmd[*i];
		(*i)++;
	}
	str[j] = '\0';
	return (ft_strdup(str));
}

char	*token_special(char *cmd, int *i)
{
	char	*token;

	if (cmd[*i] == '>' || cmd[*i] == '<' || cmd[*i] == '&')
	{
		if (cmd[*i] == cmd[*i + 1])
		{
			token = ft_calloc(sizeof(char), 3);
			token[0] = cmd[*i];
			token[1] = cmd[*i + 1];
			token[2] = '\0';
			(*i) += 2;
			return (token);
		}
	}
	token = ft_calloc(sizeof(char), 2);
	token[0] = cmd[*i];
	token[1] = '\0';
	(*i)++;
	return (token);
}

char	*token_quote(char *cmd, int *i, char type)
{
	int		j;
	char	token[7000];

	j = 0;
	token[j++] = cmd[*i];
	(*i)++;
	while (cmd[*i] != type && cmd[*i])
	{
		token[j++] = cmd[*i];
		(*i)++;
	}
	if (cmd[*i] == type)
		token[j++] = cmd[*i];
	token[j] = '\0';
	if (!cmd[*i])
		return (NULL);
	(*i)++;
	return (ft_strdup(token));
}

/** @brief Get the command and @returns the tokens in the format char ** */
char	**tokenize_aux(char *cmd)
{
	char	**tokens;
	int		tokens_index;
	int		i;

	i = 0;
	tokens_index = 0;
	tokens = ft_calloc(get_token_amount(cmd) + 1, sizeof(char *));
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			tokens[tokens_index] = token_quote(cmd, &i, cmd[i]);
		else if (is_special_char(cmd[i]))
			tokens[tokens_index] = token_special(cmd, &i);
		else if (ft_isspace(cmd[i]))
			tokens[tokens_index] = token_space(cmd, &i);
		else
			tokens[tokens_index] = token_cmd(cmd, &i);
		tokens_index++;
	}
	tokens[tokens_index] = NULL;
	return (tokens);
}

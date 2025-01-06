/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:02:56 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/06 12:28:43 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	token_type(char *token)
{
	if (token[0] == '|')
		return (PIPE);
	else if (!ft_strncmp(token, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp (token, "<<", 2))
		return (HERE_DOC);
	else if (token[0] == '>')
		return (REDIR);
	else if (token[0] == '<')
		return (REDIR_MQ);
	else if (ft_isspace(token[0]))
		return (IS_SPACE);
	else if (!ft_strncmp(token, "\"\"", ft_strlen(token)))
		return (IS_NULL);
	else if (!ft_strncmp(token, "\'\'", ft_strlen(token)))
		return (IS_NULL);
	else if (token[0] == '\'')
		return (S_QUOTES);
	else if (token[0] == '"')
		return (D_QUOTES);
	else
		return (CMD);
}

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
		else if (cmd[i] && !is_special_char(cmd[i]) && !ft_isspace(cmd[i]))
		{
			while (cmd[i] && !is_special_char(cmd[i]) && !ft_isspace(cmd[i])
				&& (cmd[i] != '"' && cmd[i] != '\''))
				i++;
			amount++;
		}
	}
	return (amount);
}

void	tokenize(t_main *pgr, char *cmd)
{
	char	**tokens;
	int		i;

	i = 0;
	tokens = tokenize_aux(cmd);
	pgr->token_amount = get_token_amount(cmd);
	pgr->tokens = NULL;
	while (i < pgr->token_amount)
		add_node(&pgr->tokens, tokens[i++]);
	free_double_array(tokens);
}

int	order_tokens(t_main **pgr)
{
	t_token	*remove;
	t_token	*start;
	char	*aux;

	aux = NULL;
	remove = NULL;
	start = NULL;
	if (join_tokens(&(*pgr)->tokens, remove, start, aux))
	{
		free_tmain((*pgr), 0);
		return (1);
	}
	return (0);
}

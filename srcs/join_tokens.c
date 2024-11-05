/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:38:03 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/05 12:31:30 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	iscmd_or_quotes(int type)
{
	if (type == CMD)
		return (1);
	if (type == S_QUOTES)
		return (2);
	if (type == D_QUOTES)
		return (3);
	return (0);
}

/** @brief Remove the first and last quote by the token */
void	remove_quotes(t_token **head)
{
	t_token	*cur;
	int		len;

	cur = (*head);
	while (cur != NULL)
	{
		if (cur->type == S_QUOTES || cur->type == D_QUOTES)
		{
			len = ft_strlen(cur->content);
			if (len > 1 && ((cur->content[0] == '\''
						&& cur->content[len - 1] == '\'')
					|| (cur->content[0] == '"'
						&& cur->content[len - 1] == '"')))
			{
				ft_memmove(cur->content, cur->content + 1, len - 2);
				cur->content[len - 2] = '\0';
				cur->c_len = ft_strlen(cur->content);
			}
		}
		cur = cur->next;
	}
}

void	join_tokens(t_token **tokens)
{
	t_token	*remove;
	t_token	*start;

	start = *tokens;
	remove_quotes(tokens);
	while (*tokens && (*tokens)->next)
	{
		if (iscmd_or_quotes((*tokens)->type)
			&& iscmd_or_quotes((*tokens)->next->type))
		{
			(*tokens)->content = ft_strjoin((*tokens)->content,
					(*tokens)->next->content);
			(*tokens)->c_len = ft_strlen((*tokens)->content);
			remove = (*tokens)->next;
			(*tokens)->next = (*tokens)->next->next;
			if ((*tokens)->next)
				(*tokens)->next->prev = (*tokens);
			free (remove);
		}
		if ((*tokens)->next)
			(*tokens) = (*tokens)->next;
		else
			break ;
	}
	(*tokens) = start;
}

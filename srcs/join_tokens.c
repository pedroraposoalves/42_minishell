/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:38:03 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/04 19:00:39 by malves-b         ###   ########.fr       */
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_quotes(t_token *head)
{
	t_token *cur;

	cur = head;
	while (cur != NULL) {
		if (cur->type == S_QUOTES || cur->type == D_QUOTES)
		{
			remove_quotes(cur->content);
			int len = strlen(cur->content);
			if (len > 1 && ((cur->content[0] == '\'' && cur->content[len - 1] == '\'')
				|| (cur->content[0] == '"' && cur->content[len - 1] == '"')))
			{
				ft_memmove(cur->content, cur->content + 1, len - 2);
				cur->content[len - 2] = '\0';
			}
		}
		cur = cur->next;
	}
}

void	join_tokens(t_token **tokens)
{
	t_token	*remove;
	t_token *start;

	start = *tokens;
	while (*tokens)
	{
		if (iscmd_or_quotes((*tokens)->type) && iscmd_or_quotes((*tokens)->next->type))
		{
			join_cmd(&(*tokens), (*tokens)->next->content);
			remove = (*tokens)->next;
			((*tokens)->next = (*tokens)->next->next);
			free (remove);
		}
		(*tokens) = (*tokens)->next;
		// else if (iscmd_or_quotes((*tokens)) == 2 || iscmd_or_quotes((*tokens)) == 3)
		// {
		// 	remove_quotes();
		// 	continue ;
		// }
		// else if ((*tokens)->type == IS_SPACE)
		// 	continue ;
		// else if ((*tokens)->type == )
	}
	(*tokens) = start;
}

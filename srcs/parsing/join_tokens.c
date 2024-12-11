/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:38:03 by malves-b          #+#    #+#             */
/*   Updated: 2024/12/11 15:44:05 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	remove_node(t_token **head, t_token **node)
{
	t_token	*remove;

	remove = (*node);
	if (!remove->prev)
	{
		*head = remove->next;
		if (*head)
			(*head)->prev = NULL;
	}
	else if (!remove->next)
		remove->prev->next = NULL;
	else
	{
		remove->prev->next = remove->next;
		remove->next->prev = remove->prev;
	}
	free (remove);
	(*node) = (*head);
}

/** @brief Remove the null node of the token list */
int	remove_null(t_token **head)
{
	t_token	*current;
	t_token	*next_node;

	current = (*head);
	if ((current->c_len == 0 || current->type == IS_NULL
			|| current->type == IS_SPACE) && !current->next)
		return (1);
	while (current && current->next)
	{
		if ((current->type == IS_NULL || current->c_len == 0)
			&& (current->prev->type != IS_SPACE
				|| current->next->type != IS_SPACE))
		{
			next_node = current->next;
			remove_node(head, &current);
			current = next_node;
		}
		else
			current = current->next;
	}
	return (0);
}

int	join_tokens(t_token **tk, t_token *remove, t_token *start)
{
	remove_quotes(tk);
	if (remove_null(tk))
		return (1);
	start = *tk;
	while (*tk && (*tk)->next)
	{
		if (iscmd_or_quotes((*tk)->type) && iscmd_or_quotes((*tk)->next->type))
		{
			(*tk)->content = ft_strjoin((*tk)->content, (*tk)->next->content);
			(*tk)->c_len = ft_strlen((*tk)->content);
			remove = (*tk)->next;
			(*tk)->next = (*tk)->next->next;
			if ((*tk)->next)
				(*tk)->next->prev = (*tk);
			free (remove);
			continue ;
		}
		if ((*tk)->next)
			(*tk) = (*tk)->next;
		else
			break ;
	}
	(*tk) = start;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:17:40 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/06 16:14:09 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Add a word in the (char **) */
char	**add_word(char **args, char *new_word)
{
	char	**new_args;
	int		i;

	i = 0;
	while (args && args[i])
		i++;
	new_args = ft_calloc(sizeof(char *), i + 2);
	if (!new_args)
		return (NULL);
	i = -1;
	while (args && args[++i])
	{
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
		{
			free_double_array(new_args);
			return (NULL);
		}
	}
	new_args[++i] = ft_strdup(new_word);
	new_args[++i] = NULL;
	if (args)
		free_double_array(args);
	return (new_args);
}

/** @brief Function build multiple redir nodes*/
void	*mult_redir(t_token *start, t_token *end, t_exec *exec_node)
{
	t_redir	*new_redir;

	new_redir = create_redir_node();
	while (start->id < end->id)
	{
		if (start->type == IS_SPACE)
			continue ;
		if (start->type == CMD)
			new_redir->file = start->content;
		if (search_redir(&start, end->id))
		{
			new_redir->next = mult_redir(start, end, exec_node);
			return (new_redir);
		}
		else
		{
			new_redir->next = exec_node;
			return (new_redir);
		}
		*start = *start->next;
	}
	return (NULL);
}

t_redir	*redir_aux(t_token **start, t_token *end, t_exec *exec_node)
{
	t_redir	*redir_node;

	if (search_redir(&(*start)->next, end->id))
	{
		redir_node = mult_redir((*start)->next, end, exec_node);
	}
	else
	{
		redir_node = create_redir_node();
		redir_node->type = (*start)->type;
		redir_node->next = exec_node;
		while ((*start)->id < end->id)
		{
			if ((*start)->type == IS_SPACE)
				continue ;
			else if ((*start)->type == CMD || (*start)->type == S_QUOTES
				|| (*start)->type == D_QUOTES)
				redir_node->file = ft_strdup((*start)->content);
			(*start) = (*start)->next;
		}
	}
	return (redir_node);
}

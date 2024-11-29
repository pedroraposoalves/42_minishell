/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:17:40 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/25 23:49:46 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	i = 0;
	while (args && args[i])
	{
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
		{
			free_double_array(new_args);
			return (NULL);
		}
		i++;
	}
	new_args[i] = ft_strdup(new_word);
	new_args[i + 1] = NULL;
	if (args)
		free_double_array(args);
	return (new_args);
}

/** @brief Function build multiple redir nodes*/
void	*mult_redir(t_token *start, t_exec *exec_node, int type)
{
	t_redir	*new_redir;
	t_token	*aux;

	new_redir = create_redir_node();
	new_redir->type = type;
	while (start && start->type != PIPE)
	{
		if (start->type == CMD && new_redir->file)
			exec_node->argv = add_word(exec_node->argv, start->content);
		else if (start->type == CMD)
			new_redir->file = start->content;
		if (start->type == REDIR || start->type == REDIR_MQ
			|| start->type == APPEND || start->type == HERE_DOC)
		{
			aux = (*start).next;
			if (search_redir(&aux, 0))
				new_redir->next = mult_redir((*start).next, exec_node,
						(*start).type);
			else
				new_redir->next = redir_aux(&start, exec_node);
			return (new_redir);
		}
		*start = *start->next;
	}
	return (NULL);
}

t_redir	*redir_aux(t_token **start, t_exec *exec_node)
{
	t_redir	*redir_node;
	t_token	*aux;

	aux = (*start)->next;
	if (search_redir(&aux, 0))
		redir_node = mult_redir((*start)->next, exec_node, (*start)->type);
	else
	{
		redir_node = create_redir_node();
		redir_node->type = (*start)->type;
		redir_node->next = exec_node;
		while ((*start) && (*start)->type != PIPE)
		{
			if (((*start)->type == CMD || (*start)->type == S_QUOTES
					|| (*start)->type == D_QUOTES) && redir_node->file)
				exec_node->argv = add_word(exec_node->argv, (*start)->content);
			else if ((*start)->type == CMD || (*start)->type == S_QUOTES
				|| (*start)->type == D_QUOTES)
				redir_node->file = ft_strdup((*start)->content);
			if (!(*start)->next)
				break ;
			(*start) = (*start)->next;
		}
	}
	return (redir_node);
}

/** @brief Check if the list has a redir */
int	search_redir(t_token **token, int limit)
{
	t_token	*current;

	current = (*token);
	while (current && (limit == 0 || current->id < limit)
		&& current->type != PIPE)
	{
		if (current->type == REDIR || current->type == REDIR_MQ
			|| current->type == HERE_DOC || current->type == APPEND)
		{
			(*token) = current;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

/** @brief Check if the list has a pipe */
int	search_pipe(t_token **token, int limit)
{
	t_token	*current;

	current = (*token);
	while (current && (limit == 0 || current->id < limit))
	{
		if (current->type == PIPE)
		{
			(*token) = current;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

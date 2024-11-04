/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:03:05 by malves-b          #+#    #+#             */
/*   Updated: 2024/10/30 15:49:30 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Check if the list has a redir */
int	search_redir(t_token **token, int *i)
{
	t_token	*start;

	start = *token;
	if (!*i || !i)
	{
		while (token)
		{
			if (((*token)->type == REDIR) || ((*token)->type == REDIR_MQ)
				|| ((*token)->type == HERE_DOC) || ((*token)->type == APPEND))
				return (1);
			else if ((*token)->next)
				*token = (*token)->next;
			else
				break ;
		}
	}
	while ((*token)->id < *i && (i || *i))
	{
		if (((*token)->type == REDIR) || ((*token)->type == REDIR_MQ)
			|| ((*token)->type == HERE_DOC) || ((*token)->type == APPEND))
			return (1);
		*token = (*token)->next;
	}
	*token = start;
	return (0);
}

/** @brief Check if the list has a pipe */
int	search_pipe(t_token **token, int *i)
{
	t_token	*start;

	start = *token;
	if (!*i || !i)
	{
		while (token)
		{
			if ((*token)->type == PIPE)
				return (1);
			else if ((*token)->next)
				*token = (*token)->next;
			else
				break ;
		}
	}
	while ((*token)->id < *i && (i || *i))
	{
		if ((*token)->type == PIPE)
			return (1);
		*token = (*token)->next;
	}
	*token = start;
	return (0);
}

/** @brief alloc a node type t_exec and start content = NULL
 * / arg_len = 0 / type = CMD
 */
t_exec	*create_exec_node(void)
{
	t_exec	*cmd;

	cmd = (t_exec *)malloc(sizeof(t_exec));
	cmd->args = NULL;
	cmd->type = CMD;
	return (cmd);
}

/** @brief alloc a node type t_redir and start cmd = NULL /
 *  fd = -1 / file = NULL
 */
t_redir	*create_redir_node(void)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	redir->type = NULL;
	redir->next = NULL;
	redir->file = NULL;
	return (redir);
}

/** @brief alloc a node type t_pipe and start *left = NULL / *
 *  right = NULL / type
 */
t_pipe	*create_pipe_node(void)
{
	t_pipe	*pipe_node;

	pipe_node = (t_pipe *)malloc(sizeof(t_pipe));
	pipe_node->left = NULL;
	pipe_node->right = NULL;
	pipe_node->type = PIPE;
	return (pipe_node);
}

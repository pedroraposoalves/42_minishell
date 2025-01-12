/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:03:27 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/12 16:41:02 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_main	*init_main(char **envp)
{
	t_main	*pgr;
	int		i;

	pgr = (t_main *)malloc(sizeof(t_main));
	pgr->tokens = NULL;
	pgr->root = NULL;
	pgr->ctrld = 0;
	pgr->cur_envp = NULL;
	pgr->exit_status[0] = 0;
	pgr->exit_status[1] = 0;
	if (!envp)
		return (pgr);
	i = 0;
	while (envp[i])
		i++;
	pgr->cur_envp = (char **)malloc(sizeof(char *) * (i + 1));
	pgr->cur_envp[i--] = NULL;
	while (i >= 0)
	{
		pgr->cur_envp[i] = ft_strdup(envp[i]);
		i--;
	}
	return (pgr);
}

void	add_node(t_token **current, char *token)
{
	t_token	*new_node;
	t_token	*last_node;

	new_node = malloc(sizeof(t_token));
	new_node->content = ft_strdup(token);
	new_node->type = token_type(token);
	new_node->c_len = ft_strlen(token);
	if (*current == NULL)
	{
		new_node->id = 0;
		new_node->prev = NULL;
		new_node->next = NULL;
		*current = new_node;
	}
	else
	{
		last_node = *current;
		while (last_node->next)
			last_node = last_node->next;
		new_node->id = last_node->id + 1;
		new_node->prev = last_node;
		new_node->next = NULL;
		last_node->next = new_node;
	}
}

/** @brief alloc a node type t_exec and start content = NULL
 * / arg_len = 0 / type = CMD
 */
t_exec	*create_exec_node(void)
{
	t_exec	*cmd;

	cmd = (t_exec *)malloc(sizeof(t_exec));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->type = CMD;
	return (cmd);
}

/** @brief alloc a node type t_redir and start cmd = NULL /
 *  fd = -1 / file = NULL
 */
t_redir	*create_redir_node(int type)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = REDIR;
	redir->next = NULL;
	redir->file = NULL;
	if (type)
		redir->type = type;
	return (redir);
}

/** @brief alloc a node type t_pipe and start *left = NULL / *
 *  right = NULL / type
 */
t_pipe	*create_pipe_node(void)
{
	t_pipe	*pipe_node;

	pipe_node = (t_pipe *)malloc(sizeof(t_pipe));
	if (!pipe_node)
		return (NULL);
	pipe_node->left = NULL;
	pipe_node->right = NULL;
	pipe_node->type = PIPE;
	return (pipe_node);
}

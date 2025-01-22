/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:09:01 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/22 11:56:18 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

t_exec	*parse_exec_aux(t_token **cur, int limit, t_exec *exec_node)
{
	while (*cur && (*cur)->id < limit)
	{
		if ((*cur)->type == CMD || (*cur)->type == D_QUOTES
			|| (*cur)->type == S_QUOTES)
			exec_node->argv = add_word(exec_node->argv, (*cur)->content);
		if ((*cur)->next)
			(*cur) = (*cur)->next;
	}
	return (exec_node);
}

t_exec	*parse_exec(t_token **cur, int limit)
{
	t_exec	*exec_node;

	exec_node = create_exec_node();
	if (!limit)
	{
		while (*cur)
		{
			if ((*cur)->type == CMD || (*cur)->type == D_QUOTES
				|| (*cur)->type == S_QUOTES)
				exec_node->argv = add_word(exec_node->argv, (*cur)->content);
			if (exec_node->argv)
			{
				if ((*cur)->type == IS_NULL && (ft_strncmp(exec_node->argv[0], \
					"cd", ft_strlen(exec_node->argv[0])) == 0
						|| ft_strncmp(exec_node->argv[0], "export",
						ft_strlen(exec_node->argv[0])) == 0))
					exec_node->argv = add_word(exec_node->argv, "\0");
			}
			(*cur) = (*cur)->next;
		}
	}
	else
		exec_node = parse_exec_aux(cur, limit, exec_node);
	return (exec_node);
}

/* -------------------------------------------------------------------------- */

t_redir	*parse_redir(t_token **start)
{
	t_redir	*redir_node;
	t_exec	*exec_node;

	exec_node = create_exec_node();
	while ((*start) && (*start)->type != PIPE)
	{
		if ((*start)->type == CMD || (*start)->type == S_QUOTES
			|| (*start)->type == D_QUOTES)
			exec_node->argv = add_word(exec_node->argv, (*start)->content);
		else if ((*start)->type == REDIR || (*start)->type == APPEND
			|| (*start)->type == REDIR_MQ || (*start)->type == HERE_DOC)
		{
			redir_node = redir_aux(start, exec_node);
			return (redir_node);
		}
		(*start) = (*start)->next;
	}
	return (NULL);
}

t_pipe	*parse_pipe(t_token **start, t_token **cur, t_token *ptr_aux)
{
	t_pipe	*pipe;

	pipe = create_pipe_node();
	ptr_aux = (*start);
	while ((*start))
	{
		if (search_redir(&ptr_aux, (*cur)->id) && !pipe->left)
			pipe->left = parse_redir(start);
		else if (!pipe->left)
			pipe->left = parse_exec(start, (*cur)->id);
		if ((*start)->id == (*cur)->id)
		{
			(*cur) = (*cur)->next;
			(*start) = (*start)->next;
			if (search_redir(cur, 0))
				pipe->right = parse_redir(start);
			else if (search_pipe(cur, 0))
				pipe->right = parse_pipe(start, cur, ptr_aux);
			else
				pipe->right = parse_exec(start, 0);
			return (pipe);
		}
		start = &(*start)->next;
	}
	return (pipe);
}

void	*start_parsing(t_token *start)
{
	t_token	*cur;
	t_token	*ptr_aux;

	ptr_aux = NULL;
	cur = start;
	if (search_pipe(&cur, 0))
		return (parse_pipe(&start, &cur, ptr_aux));
	else if (search_redir(&cur, 0))
		return (parse_redir(&start));
	else
		return (parse_exec(&start, 0));
}

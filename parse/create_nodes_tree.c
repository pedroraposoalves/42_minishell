/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:09:01 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/06 13:49:17 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec	*parse_exec(t_token **cur, int limit)
{
	t_exec	*exec_node;

	exec_node = create_exec_node();
	if (!limit)
	{
		while (*cur)
		{
			if ((*cur)->content == CMD)
				exec_node->args = add_word(exec_node->args, (*cur)->content);
			if ((*cur)->next)
				(*cur) = (*cur)->next;		
		}
	}
	else
	{
		while (*cur && (*cur)->id < limit)
		{
			if ((*cur)->content == CMD)
				exec_node->args = add_word(exec_node->args, (*cur)->content);
			if ((*cur)->next)
				(*cur) = (*cur)->next;		
		}
	}
	return (exec_node);
}

/* -------------------------------------------------------------------------- */

t_redir	*parse_redir(t_token **start, t_token *end)
{
	t_redir	*redir_node;
	t_exec	*exec_node;

	exec_node = create_exec_node();
	while ((*start)->id < end->id)
	{
		if ((*start)->type == IS_SPACE)
			continue ;
		else if ((*start)->type == CMD || (*start)->type == S_QUOTES
			|| (*start)->type == D_QUOTES)
			exec_node->args = add_word(exec_node->args, (*start)->content);
		else if ((*start)->type == REDIR || (*start)->type == APPEND
			|| (*start)->type == REDIR_MQ || (*start)->type == HERE_DOC)
		{
			redir_node = redir_aux(start, end, exec_node);
			return (redir_node);
		}
		(*start) = (*start)->next;
	}
}

/* -------------------------------------------------------------------------- */

t_pipe	*parse_pipe(t_token **start, t_token **cur)
{
	t_pipe	*pipe;
	t_token	*ptr_aux;

	pipe = create_pipe_node();
	ptr_aux = (*start);
	while ((*start)->id < (*cur)->id)
	{
		if (search_redir(ptr_aux, (*cur)->id))
			pipe->left = parse_redir(start, cur);
		else
			pipe->left = parse_exec(start, (*cur)->id);
		if ((*start)->id + 1 == (*cur)->id)
		{
			(*start) = (*cur);
			if (search_pipe(cur, NULL))
				pipe->right = parse_pipe(start, cur);
			else if (search_redir(cur, NULL))
				pipe->right = parse_redir(start, cur);
			else
				pipe->right = parse_exec(start, NULL);
		}
		start = (*start)->next;
	}
}

void	*start_parsing(t_token *start)
{
	t_token	*cur;
	
	cur = start;
	if (search_pipe(&cur, NULL))
		return (parse_pipe(&start, &cur));
	else if (search_redir(&cur, NULL))
		return (parse_redir(&start, &cur));
	else
		return (parse_exec(&start, NULL));
}

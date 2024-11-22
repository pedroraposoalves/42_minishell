/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:58:39 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/21 22:58:03 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tmain(t_main *pgr)
{
	while (pgr->tokens->next)
	{
		pgr->tokens = pgr->tokens->next;
		free (pgr->tokens->prev->content);
		free (pgr->tokens->prev);
	}
	free (pgr->tokens->content);
	free (pgr->tokens);
	free_double_array (pgr->cur_envp);
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_redir_node(void *root)
{
	t_redir	*redir;
	t_exec	*exec;
	int		type;

	exec = NULL;
	if (!root)
		return ;
	redir = (t_redir *)root;
	free(redir->file);
	type = *(int *)redir->next;
	if (type == CMD)
	{
		exec = (t_exec *)redir->next;
		free_double_array(exec->args);
		free(exec);
	}
	else
		free_redir_node(redir->next);
	free(redir);
}

void	free_tree(void *root)
{
	int		type;
	t_exec	*exec;
	t_pipe	*pipe;

	if (!root)
		return ;
	type = *((int *)root);
	if (type == PIPE)
	{
		pipe = (t_pipe *)root;
		free_tree(pipe->left);
		free_tree(pipe->right);
		free(pipe);
	}
	else if (type == REDIR || type == REDIR_MQ || type == APPEND
		|| type == HERE_DOC)
		free_redir_node(root);
	else
	{
		exec = (t_exec *)root;
		free_double_array(exec->args);
		free(exec);
	}
}

void	free_all(t_main *pgr, void *root)
{
	free_tmain(pgr);
	free_tree(root);
	free(pgr);
}

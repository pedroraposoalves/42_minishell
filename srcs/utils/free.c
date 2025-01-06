/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:58:39 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/06 12:32:30 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tmain(t_main *pgr, int exit_flag)
{
	t_token	*tmp;

	while (pgr->tokens)
	{
		tmp = pgr->tokens;
		pgr->tokens = pgr->tokens->next;
		if (tmp->content)
		{
			free (tmp->content);
			tmp->content = NULL;
		}
		if (tmp)
		{
			free (tmp);
			tmp = NULL;
		}
	}
	if (exit_flag)
		free_double_array (pgr->cur_envp);
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	if (array && array[i])
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
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
	if (redir->file)
	{
		free(redir->file);
		redir->file = NULL;
	}
	type = *(int *)redir->next;
	if (type == CMD)
	{
		exec = (t_exec *)redir->next;
		free_double_array(exec->argv);
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
		free_double_array(exec->argv);
		free(exec);
	}
}

int	free_all(t_main *pgr, void *root, int exit_flag)
{
	int	status;

	status = pgr->exit_status[1];
	free_tmain(pgr, exit_flag);
	free_tree(root);
	free(pgr);
	return (status);
}

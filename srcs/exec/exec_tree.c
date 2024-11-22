/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:42:58 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/21 22:55:50 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pipe(void *node, t_main *pgr)
{
	t_pipe	*pipe_node;
	int		p[2];
	int		pid1, pid2;

	pipe_node = (t_pipe *)node;
	if (pipe(p) < 0)
	{
		print_err("pipe failed");
		exit(1);
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		// Processo filho esquerdo
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		exec_tree(pipe_node->left, pgr);
		exit(0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		// Processo filho direito
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
		exec_tree(pipe_node->right, pgr);
		exit(0);
	}
	close(p[0]);
	close(p[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	exec_tree(void *root, t_main *pgr)
{
	int	type;

	type = *((int *)root);
	if (!root)
		return ;
	if (type == CMD)
		ft_exec(root, pgr);
	else if (type == PIPE)
		ft_pipe(root, pgr);
	else
		ft_redir(root, pgr);

}


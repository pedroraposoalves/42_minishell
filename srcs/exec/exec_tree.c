/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:42:58 by malves-b          #+#    #+#             */
/*   Updated: 2024/12/03 17:39:45 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	end_pipe(t_main *pgr, int p[2], int pid[2])
{
	int	status[2];

	close(p[0]);
	close(p[1]);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	if (WIFEXITED(pgr->exit_status[1]))
		pgr->exit_status[1] = WEXITSTATUS(status[1]);
	if (status[1] / 256 == 130 || status[0] / 256 == 130)
		printf("\n");
	return (EXIT_SUCCESS);
}

void	ft_pipe_child(int p[2], t_main *pgr, t_pipe *pipe_node, int pid)
{
	if (!pid)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		exec_tree(pipe_node->left, pgr);
	}
	else
	{
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
		exec_tree(pipe_node->right, pgr);
	}
	free_all(pgr, pgr->root, 1);
	exit (0);
}

void	ft_pipe(void *node, t_main *pgr)
{
	t_pipe	*pipe_node;
	int		p[2];
	int		pid[2];

	pipe_node = (t_pipe *)node;
	if (pipe(p) < 0)
	{
		print_error("minishell:", "pipe failed", NULL, NULL);
		exit(1);
	}
	pid[0] = fork();
	if (pid[0] == 0)
		ft_pipe_child(p, pgr, pipe_node, 0);
	pid[1] = fork();
	if (pid[1] == 0)
		ft_pipe_child(p, pgr, pipe_node, 1);
	end_pipe(pgr, p, pid);
}


void	exec_tree(void *root, t_main *pgr)
{
	int	type;

	if (!root)
		return ;
	type = *((int *)root);
	if (type == CMD)
		ft_exec(root, pgr);
	else if (type == PIPE)
		ft_pipe(root, pgr);
	else
		ft_redir(root, pgr);
}


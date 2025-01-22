/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:42:58 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/22 11:57:10 by malves-b         ###   ########.fr       */
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
		exec_tree(pipe_node->left, pgr);
		close(p[1]);
	}
	else
	{
		dup2(p[0], STDIN_FILENO);
		close(p[1]);
		exec_tree(pipe_node->right, pgr);
		close(p[0]);
	}
	free_all(pgr, pgr->root, 1);
	exit (0);
}

void	ft_pipe(void *node, t_main *pgr)
{
	t_pipe	*pipe_node;
	int		p[2];
	int		pid[2];

	pipe_signals();
	pipe_node = (t_pipe *)node;
	if (pipe(p) < 0)
	{
		print_error(SHELL_NAME, "pipe failed", NULL, NULL);
		exit(1);
	}
	pid[0] = fork();
	if (pid[0] == 0)
	{
		child_signals();
		ft_pipe_child(p, pgr, pipe_node, 0);
	}
	pid[1] = fork();
	if (pid[1] == 0)
		ft_pipe_child(p, pgr, pipe_node, 1);
	end_pipe(pgr, p, pid);
}

void	ft_update_env_last_command(t_main *pgr, t_exec *node)
{
	char	*path;
	int		i;

	if (!node->argv || !node->argv[0])
		return ;
	i = matrix_len(node->argv) - 1;
	path = find_path(node->argv[i], pgr);
	if (path)
	{
		if (set_env_value("_", pgr, path) == EXIT_FAILURE)
		{
			append_env_value("_", pgr);
			set_env_value("_", pgr, path);
		}
		free(path);
	}
	else
	{
		if (set_env_value("_", pgr, node->argv[i]) == EXIT_FAILURE)
		{
			append_env_value("_", pgr);
			set_env_value("_", pgr, node->argv[i]);
		}
	}
}

void	exec_tree(void *root, t_main *pgr)
{
	if (!root)
		return ;
	if (*((int *)root) == CMD)
	{
		ft_update_env_last_command(pgr, (t_exec *) root);
		ft_exec(root, pgr, 0);
	}
	else if (*((int *)root) == PIPE)
		ft_pipe(root, pgr);
	else if (!check_cmd_is_empty(root))
		ft_redir(root, pgr, 0);
}

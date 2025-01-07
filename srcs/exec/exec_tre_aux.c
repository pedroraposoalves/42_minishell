/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tre_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:13:16 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/06 13:33:27 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_infile(t_main *pgr, t_redir *redir_node)
{
	int	fd;
	int	stdin_backup;

	if (!redir_node->file)
		return (0);
	if (access(redir_node->file, F_OK) != 0)
	{
		print_error(SHELL_NAME, redir_node->file, NULL,
			"No such file or directory");
		return (0);
	}
	fd = open(redir_node->file, O_RDONLY);
	if (fd == -1)
	{
		print_error(SHELL_NAME, redir_node->file, NULL, "Permission denied");
		pgr->exit_status[1] = EXIT_FAILURE;
		return (0);
	}
	stdin_backup = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close (fd);
	exec_tree(redir_node->next, pgr);
	dup2(stdin_backup, STDIN_FILENO);
	close (fd);
	return (1);
}

void	ft_redir(void *node, t_main *pgr)
{
	t_redir	*redir_node;
	int		fd;
	int		stdout_backup;

	fd = 0;
	redir_node = (t_redir *)node;
	if (redir_node->type == REDIR)
		fd = open(redir_node->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir_node->type == APPEND)
		fd = open(redir_node->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redir_node->type == REDIR_MQ)
		ft_infile(pgr, redir_node);
	if (redir_node->type == REDIR_MQ)
		return ;
	if (fd < 0)
	{
		print_error(SHELL_NAME, "cannot open file", NULL, NULL);
		free_all(pgr, pgr->root, 1);
		exit(1);
	}
	stdout_backup = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	exec_tree(redir_node->next, pgr);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdout_backup);
}

void	ft_exec(void *node, t_main *pgr, int status)
{
	t_exec	*exec_node;
	int		pid;

	exec_node = (t_exec *)node;
	if (!exec_node->argv)
		return ;
	if (isbuiltin(exec_node->argv[0]))
	{
		call_builtin(isbuiltin(exec_node->argv[0]), node, pgr, pgr->root);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		print_error(SHELL_NAME, "fork failed", NULL, NULL);
		exit(1);
	}
	if (pid == 0)
	{
		status = ft_execve(exec_node, pgr->cur_envp);
		free_all(pgr, pgr->root, 1);
		exit(status);
	}
	waitpid(pid, &status, 0);
	pgr->exit_status[1] = set_exit_signal(status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tre_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:13:16 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/21 15:50:31 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_cmd_is_empty(void *node)
{
	int		type;
	t_redir	*redir;
	t_exec	*exec;

	redir = NULL;
	exec = NULL;
	while (1)
	{
		type = *((int *)node);
		if (type == CMD)
		{
			exec = (t_exec *)node;
			if (!exec->argv)
				return (1);
			return (0);
		}
		else
		{
			redir = (t_redir *)node;
			redir = redir->next;
			return (check_cmd_is_empty(redir));
		}
	}
}

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

void	ft_redir(void *node, t_main *pgr, int fd)
{
	t_redir	*redir_node;
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

int	ft_fork_aux(int status, t_exec *ex, t_main *pgr)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		print_error(SHELL_NAME, "fork failed", NULL, NULL);
		exit (1);
	}
	if (pid == 0)
	{
		child_signals();
		status = ft_execve(ex, pgr);
		free_all(pgr, pgr->root, 1);
		exit(status);
	}
	waitpid(pid, &status, 0);
	return (status);
}

void	ft_exec(void *node, t_main *pgr, int status)
{
	t_exec	*ex;

	ex = (t_exec *)node;
	if (!ex->argv)
		return ;
	if ((isbuiltin(ex->argv[0]) && isbuiltin(ex->argv[0]) != 6) \
		|| (isbuiltin(ex->argv[0]) == 6 && get_env_value("PATH", pgr)))
	{
		pgr->exit_status[1] = call_builtin(isbuiltin(ex->argv[0]), node,
				pgr, pgr->root);
		return ;
	}
	ignore_signals();
	status = ft_fork_aux(status, ex, pgr);
	setup_signals();
	pgr->exit_status[1] = set_exit_signal(status);
}

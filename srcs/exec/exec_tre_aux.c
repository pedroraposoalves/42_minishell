/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tre_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:13:16 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/10 08:19:34 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** @brief Function prints a error msg and exit program
 * @param error_msg: print error
 * @param exit_code: the exit code
 */
void	ft_exit_aux(char *error_msg, int exit_code)
{
	print_error(SHELL_NAME, error_msg, NULL, NULL);
	exit (exit_code);
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


void	ft_exec(void *node, t_main *pgr, int status)
{
	t_exec	*ex;
	int		pid;

	ex = (t_exec *)node;
	if (!ex->argv)
		return ;
	if (isbuiltin(ex->argv[0]))
		pgr->exit_status[1] = call_builtin(isbuiltin(ex->argv[0]), node,
				pgr, pgr->root);
	if (isbuiltin(ex->argv[0]))
		return ;
	ignore_signals();
	pid = fork();
	if (pid < 0)
		ft_exit_aux("fork_failed", 1);
	if (pid == 0)
	{
		child_signals();
		status = ft_execve(ex, pgr->cur_envp);
		free_all(pgr, pgr->root, 1);
		exit(status);
	}
	waitpid(pid, &status, 0);
	setup_signals();
	pgr->exit_status[1] = set_exit_signal(status);
}

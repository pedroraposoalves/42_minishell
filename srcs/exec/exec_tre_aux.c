/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tre_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:13:16 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/21 22:55:43 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redir(void *node, t_main *pgr)
{
	t_redir	*redir_node;

	redir_node = (t_redir *)node;
	int fd = open(redir_node->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_err("minishell: cannot open file");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	exec_tree(redir_node->next, pgr);
}

void	ft_exec(void *node, t_main *pgr)
{
	t_exec	*exec_node;
	int		pid;

	exec_node = (t_exec *)node;
	if (isbuiltin(exec_node->args[0]))
	{
		// Executar builtin no mesmo processo
		/* g_signal = execute_builtin(exec_node->args); */
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		print_err("fork failed");
		exit(1);
	}
	if (pid == 0)
	{
		// Processo filho
		ft_execve(exec_node, pgr->cur_envp);
		exit(0);
	}
	waitpid(pid, NULL, 0); // Esperar pelo processo filho
}



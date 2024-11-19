/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tre_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:13:16 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/19 18:05:21 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec(t_exec *exec_node)
{
	int	pid;

	if (isbuiltin(exec_node->args[0]))
	{
		/*g_signal =  **call builtin -- */
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		print_err("fork");
		return ;
	}
	if (pid == 0)
	{
		/* code */
	}
}

void	ft_execve(t_exec *exec_node, t_main *pgr)
{
	char	*absolute_path;
	
	absolute_path = find_path(exec_node->args[0], pgr->cur_envp);
	if (execve(exec_node->args[0], exec_node->args, pgr->cur_envp) != 0)
	{
		
	}
}

int	isbuiltin(char *str)
{
	if (!ft_strncmp(str, "cd", 2))
		return (1);
	else if (!ft_strncmp(str, "echo", 4))
		return (1);
	else if (!ft_strncmp(str, "pwd", 3))
		return (1);
	else if (!ft_strncmp(str, "export", 6))
		return (1);
	else if (!ft_strncmp(str, "unset", 5))
		return (1);
	else if (!ft_strncmp(str, "env", 3))
		return (1);
	else if (!ft_strncmp(str, "exit", 4))
		return (1);
	else
		return (0);
}
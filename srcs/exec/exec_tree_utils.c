/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:39:34 by malves-b          #+#    #+#             */
/*   Updated: 2024/12/11 23:20:15 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** @brief Check if the cmd is builtin*/
int	isbuiltin(char *str)
{
	if (!ft_strncmp(str, "cd", 2))
		return (1);
	else if (!ft_strncmp(str, "echo", 4))
		return (2);
	else if (!ft_strncmp(str, "pwd", 3))
		return (3);
	else if (!ft_strncmp(str, "export", 6))
		return (4);
	else if (!ft_strncmp(str, "unset", 5))
		return (5);
	else if (!ft_strncmp(str, "env", 3))
		return (6);
	else if (!ft_strncmp(str, "exit", 4))
		return (7);
	else
		return (0);
}

/** @brief Find the absolute path of the command by the envp*/
char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

/** @brief The function search the absolut path of the command and  */
int	ft_execve(t_exec *exec_node, char **envp)
{
	char	*absolute_path;

	if (!exec_node->argv || !exec_node->argv[0])
		return (0);
	absolute_path = find_path(exec_node->argv[0], envp);
	if (!exec_node->argv[0][0])
		exit(EXIT_SUCCESS);
	if (!absolute_path)
	{
		if (execve(exec_node->argv[0], exec_node->argv, envp) == -1)
		{
			print_error("minishell:", exec_node->argv[0], NULL, NULL);
			print_error("minishell:", "command not found", NULL, NULL);
			exit(127);
		}
	}
	else if (execve(absolute_path, exec_node->argv, envp) == -1)
	{
		print_error("minishell:", absolute_path, NULL, NULL);
		print_error("minishell:", "command not found", NULL, NULL);
		exit(127);
	}
	return (0);
}

int	call_builtin(int number, t_exec *node, t_main *pgr, void *root)
{
	(void)pgr;
	if (number == 1)
		return (ft_cd(node->argv[1], pgr));
	if (number == 2)
		return (ft_echo(node->argv));
	if (number == 3)
		return (ft_pwd());
	if (number == 4)
		return (ft_export(pgr, node->argv));
	if (number == 5)
		return (ft_unset(pgr, node->argv));
	if (number == 6)
		return (ft_env(pgr));
	if (number == 7)
		return (ft_exit(pgr, matrix_len(node->argv), node->argv, root));
	return (0);
}

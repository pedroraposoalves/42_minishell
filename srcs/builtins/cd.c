/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:16:32 by pemirand          #+#    #+#             */
/*   Updated: 2024/11/21 22:54:26 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Neceessário testar com base no comportamento do cd no linux, quandfo pwd e oldpwd não existem na env

int	ft_cd(char *path, t_main *pgr)
{
	char	*new_pwd;
	char	cwd[PATH_MAX];

	new_pwd = NULL;
	if (!path)
	{
		new_pwd = get_env_value("HOME", pgr) + 5;
		if (!new_pwd)
			return (print_error(SHELL_NAME, "cd", NULL, "HOME not set"), \
				EXIT_FAILURE);
	}
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		new_pwd = get_env_value("OLDPWD", pgr) + 7;
		if (!new_pwd)
			return (print_error(SHELL_NAME, "cd", NULL, "OLDPWD not set"), \
				EXIT_FAILURE);
		ft_putchar_fd('~', STDOUT_FILENO);
		ft_putendl_fd(new_pwd, STDOUT_FILENO);
	}
	if (!getcwd(cwd, PATH_MAX))
		return (print_error(SHELL_NAME, "cd", NULL, "Get cwd"), \
			EXIT_FAILURE);
	if (new_pwd != NULL)
	{
		if (chdir(new_pwd) == -1)
			return (print_error_errno(SHELL_NAME, "cd", new_pwd), EXIT_FAILURE);
	}
	else
	{
		if (chdir(path) == -1)
			return (print_error_errno(SHELL_NAME, "cd", path), EXIT_FAILURE);
	}
	if (update_pwd(pgr, cwd) == EXIT_FAILURE)
		return (print_error(SHELL_NAME, "cd", NULL, "Env Update"), \
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	update_pwd(t_main *pgr, char *old_cwd)
{
	char	new_cwd[PATH_MAX];

	if (!old_cwd)
		return (print_error(SHELL_NAME, "cd", NULL, "Env Update"), \
			EXIT_FAILURE);
	if (set_env_value("OLDPWD", pgr, old_cwd) == EXIT_FAILURE)
	{
		append_env_value("OLDPWD", pgr);
		if (set_env_value("OLDPWD", pgr, old_cwd) == EXIT_FAILURE)
			return (print_error(SHELL_NAME, "cd", NULL, "Env Update"), \
				EXIT_FAILURE);
	}
	if (!getcwd(new_cwd, PATH_MAX))
		return (print_error(SHELL_NAME, "cd", NULL, "Env Update"), \
			EXIT_FAILURE);
	if (set_env_value("PWD", pgr, new_cwd) == EXIT_FAILURE)
	{
		append_env_value("PWD", pgr);
		if (set_env_value("PWD", pgr, new_cwd) == EXIT_FAILURE)
			return (print_error(SHELL_NAME, "cd", NULL, "Env Update"), \
				EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

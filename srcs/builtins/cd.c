/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:16:32 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/22 16:53:59 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd_aux(char **argv, t_main *pgr, char *new_pwd)
{
	char	cwd[PATH_MAX];

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
		if (argv[1][0] != '\0' && chdir(argv[1]) == -1)
			return (print_error_errno(SHELL_NAME, "cd", argv[1]), EXIT_FAILURE);
	}
	if (update_pwd(pgr, cwd) == EXIT_FAILURE)
		return (print_error(SHELL_NAME, "cd", NULL, "Env Update"), \
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_cd(char **argv, t_main *pgr)
{
	char	*new_pwd;

	new_pwd = NULL;
	if (matrix_len(argv) > 2)
		return (print_error(SHELL_NAME, NULL, NULL, "too many arguments"), 1);
	if (!argv[1])
	{
		new_pwd = get_env_value("HOME", pgr);
		if (!new_pwd)
			return (print_error(SHELL_NAME, "cd", NULL, "HOME not set"), \
				EXIT_FAILURE);
		new_pwd += 5;
	}
	else if (ft_strncmp(argv[1], "-", 1) == 0)
	{
		new_pwd = get_env_value("OLDPWD", pgr);
		if (!new_pwd)
			return (print_error(SHELL_NAME, "cd", NULL, "OLDPWD not set"), \
				EXIT_FAILURE);
		new_pwd += 7;
		ft_putchar_fd('~', STDOUT_FILENO);
		ft_putendl_fd(new_pwd, STDOUT_FILENO);
	}
	return (ft_cd_aux(argv, pgr, new_pwd));
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

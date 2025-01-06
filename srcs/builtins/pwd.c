/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:35:26 by pemirand          #+#    #+#             */
/*   Updated: 2024/12/30 12:38:28 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
	{
		print_error_errno(SHELL_NAME, "pwd", NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

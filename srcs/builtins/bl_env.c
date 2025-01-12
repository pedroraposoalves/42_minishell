/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bl_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:15:06 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/11 11:35:34 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_main *pgr, char **argv)
{
	int	i;

	if (matrix_len(argv) > 1)
		return (print_error(SHELL_NAME, argv[1], NULL, \
			"No such file or directory"), 127);
	if (!pgr->cur_envp)
		return (print_error(SHELL_NAME, "env", NULL, "Env variable empty"), \
			EXIT_FAILURE);
	else
	{
		i = 0;
		while (pgr->cur_envp[i])
			ft_putendl_fd(pgr->cur_envp[i++], STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}

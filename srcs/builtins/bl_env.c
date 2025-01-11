/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bl_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:15:06 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/11 00:23:27 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_main *pgr, char **argv)
{
	int	i;

	if matrix_len(argv) > 2)
		return(print_error_errno(SHELL_NAME, argv[2], NULL));
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

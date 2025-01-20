/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bl_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:15:06 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/17 15:39:05 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_main *pgr, char **argv)
{
	int	i;

	if (matrix_len(argv) > 1)
		return (print_error(SHELL_NAME, argv[1], NULL, \
			"Ficheiro ou pasta inexistente"), 127);
	if (!pgr->cur_envp)
		return (print_error(SHELL_NAME, "env", NULL, "Env variable empty"), \
			EXIT_FAILURE);
	else
	{
		i = 0;
		while (pgr->cur_envp[i])
		{
			if (pgr->cur_envp[i][ft_str_char(pgr->cur_envp[i], '=')] == '=')
				ft_putendl_fd(pgr->cur_envp[i], STDOUT_FILENO);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

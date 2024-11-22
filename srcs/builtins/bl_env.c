/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bl_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:15:06 by pemirand          #+#    #+#             */
/*   Updated: 2024/11/21 22:54:19 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_main *pgr)
{
	int	i;

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

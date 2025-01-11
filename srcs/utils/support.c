/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:50:46 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/10 23:50:51 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	empty_cmd(t_main *pgr)
{
	printf("exit\n");
	free_double_array(pgr->cur_envp);
	free (pgr);
	exit(0);
}

void	set_exit_status(t_main *pgr)
{
	pgr->exit_status[0] = pgr->exit_status[1];
	if (g_exit != 0)
		pgr->exit_status[0] = g_exit;
	pgr->exit_status[1] = 0;
	g_exit = 0;
}

void	check_have_argument(int argc)
{
	if (argc != 1)
	{
		print_error(SHELL_NAME, "The minishell should'nt have arguments!",
			NULL, NULL);
		exit (127);
	}
}

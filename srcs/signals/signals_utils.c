/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:36:42 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/22 12:59:01 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_heredoc_signals(int signal)
{
	t_main	*pgr;

	pgr = NULL;
	if (signal == SIGINT)
	{
		close(STDIN_FILENO);
		pgr = get_pgr(NULL);
		ft_putstr_fd("\n", 2);
		if (pgr)
			free_all(pgr, pgr->root, 1);
		g_exit = 130;
		exit(130);
	}
}

void	set_heredoc_sig(void)
{
	signal(SIGINT, setup_heredoc_signals);
}

void	signal_aux(int signal)
{
	t_main	*pgr;

	(void)signal;
	pgr = get_pgr(NULL);
	free_all(pgr, pgr->root, 130);
	exit(130);
}

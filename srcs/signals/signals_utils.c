/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:36:42 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/12 12:52:26 by malves-b         ###   ########.fr       */
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
		printf("\n");
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


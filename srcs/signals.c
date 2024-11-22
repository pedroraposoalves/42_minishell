/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:32:48 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/21 22:57:36 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_sigint(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		print_err("\n");
		rl_redisplay();
		g_signal = 130;
		exit (g_signal);
	}
	else if (signal == SIGQUIT)
	{
		g_signal = 131;
		print_err("Quit (core dumped)\n");
		exit (g_signal);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, set_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

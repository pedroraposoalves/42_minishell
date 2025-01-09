/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:32:48 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/08 20:02:01 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_sigint(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		print_error(NULL, NULL, NULL, NULL);
		rl_redisplay();
		global_exit = 130;
	}
}

void	setup_signals(void)
{
	signal(SIGINT, set_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signals(void)
{
	signal(SIGINT, set_sigint);
	signal(SIGQUIT, SIG_DFL);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	pipe_signals(void)
{
	signal(SIGPIPE, signal_aux);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

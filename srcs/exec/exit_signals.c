/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:48:42 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/22 12:52:37 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_exit_signal(int exit_status)
{
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	if (WIFSIGNALED(exit_status))
	{
		if (exit_status == 2)
			ft_putstr_fd("\n", 2);
		else if (exit_status == 131)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			return (exit_status);
		}
		return (exit_status + 128);
	}
	else
		return (1);
}

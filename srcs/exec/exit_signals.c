/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:48:42 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/08 19:58:27 by malves-b         ###   ########.fr       */
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
			printf("\n");
		else if (exit_status == 131)
		{
			printf("Quit (core dumped)\n");
			return (exit_status);
		}
		return (exit_status + 128);
	}
	else
		return (1);
}

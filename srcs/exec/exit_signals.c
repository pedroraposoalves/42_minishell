/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:48:42 by malves-b          #+#    #+#             */
/*   Updated: 2024/12/10 16:59:53 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_exit_signal(int exit_status)
{
	if (WIFEXITED(exit_status))
    	return (WEXITSTATUS(exit_status));
	else
    	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:36:42 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/08 16:48:19 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_aux(int signal)
{
	t_main	*pgr;

	(void)signal;
	pgr = get_pgr(NULL);
	free_all(pgr, pgr->root, 130);
	exit(130);
}
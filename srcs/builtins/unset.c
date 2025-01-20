/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:01:27 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/19 22:50:11 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//quando uma variável não existe este ignora e passa à proxima,
//testar se o comportamento é o mesmo no linux

int	ft_unset(t_main *pgr, char **argv)
{
	if (!pgr->cur_envp)
		return (EXIT_FAILURE);
	while (*argv)
	{
		del_env_value(*argv, pgr);
		argv++;
	}
	return (EXIT_SUCCESS);
}

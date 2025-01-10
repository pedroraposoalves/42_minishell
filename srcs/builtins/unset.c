/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:01:27 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/10 20:18:30 by pemirand         ###   ########.fr       */
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
		if (ft_strlen(*argv) == 1 && argv[0][0] == '_')
		{
				argv++;
				continue;
		}
		del_env_value(*argv, pgr);
		argv++;
	}
	return (EXIT_SUCCESS);
}

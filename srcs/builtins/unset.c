/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:01:27 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/20 22:16:12 by pemirand         ###   ########.fr       */
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
		if (argv[0][0] == '_')
		{
			del_env_value(*argv, pgr);
			append_env_value("_", pgr);
		}
		else
			del_env_value(*argv, pgr);
		argv++;
	}
	return (EXIT_SUCCESS);
}

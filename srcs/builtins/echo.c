/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:30:27 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/22 17:43:12 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **argv)
{
	int	i;
	int	nl_flag;

	i = 1;
	nl_flag = 0;
	while (argv[i] && ft_strncmp(argv[i], "-n", ft_strlen(argv[i])) == 0)
		i++;
	if (i == 1)
		nl_flag = 1;
	while (argv[i])
	{
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
		if (argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (nl_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

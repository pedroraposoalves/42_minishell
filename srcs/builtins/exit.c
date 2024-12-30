/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:25:10 by pemirand          #+#    #+#             */
/*   Updated: 2024/12/03 17:41:36 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_is_number(char *number);

/*testar para comenados do género ls | exit ou outrop builtin */

int	ft_exit(t_main *pgr, int argc, char **argv, void *root)
{
	int	exit_num;

	exit_num = pgr->exit_status[0];
	exit_num = 0;
	if (argc > 2)
		return (print_error(SHELL_NAME, "exit", NULL, \
			"too many arguments"), EXIT_FAILURE);
	if (argc == 2)
	{
		exit_num = check_is_number(argv[1]);
		if (exit_num == 0)
			exit_num = ft_atoi(argv[1]);
		else if (exit_num < 0)
			exit_num = 2;
		else
		{
			print_error(SHELL_NAME, "bad math expression", \
				"operator expected at", argv[1] + exit_num);
			exit_num = 2;
		}
	}
	free_all(pgr, root, 1);
	exit(exit_num);
}

int	check_is_number(char *number)
{
	int	i;

	i = 0;
	if (!number || ft_isalpha(number[i]) || (number[i] == '-' \
		&& (number[i + 1] == '\0' || ft_isalpha(number[i + 1]))))
		return (-1);
	if (number[i] == '-')
		i++;
	while (number[i] != '\0')
	{
		if (ft_isalpha(number[i++]))
			return (i);
	}
	return (0);
}

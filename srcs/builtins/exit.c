/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:25:10 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/10 19:24:30 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_is_number(char *number);

/*testar para comenados do género ls | exit ou outrop builtin */

int	ft_exit(t_main *pgr, int argc, char **argv, void *root)
{
	int	exit_num;
	int	is_number;

	exit_num = 0;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (argc == 1)
		exit(EXIT_SUCCESS);
	is_number = check_is_number(argv[1]);
	if (argc > 1 && is_number < 0)
	{
		exit_num = 2;
		print_error(SHELL_NAME, "exit", argv[1], "numeric argument required");
	} 
	else if (argc > 2)
		return (print_error(SHELL_NAME, "exit", NULL, "too many arguments"), EXIT_FAILURE);
	else if (argc > 1 && is_number == 0)
		exit_num = ft_atoi(argv[1]);
	free_all(pgr, root, 1);
	exit(exit_num % 256);
}

int	check_is_number(char *number)
{
	int	i;
	int	z;

	i = 0;
	if (!number || ft_isalpha(number[i]) || (number[i] == '-' \
		&& (number[i + 1] == '\0' || ft_isalpha(number[i + 1]))))
		return (-1);
	if (number[i] == '-' || number[i] == '+')
		i++;
	while (number[i] == '0')
		i++;
	z = 0;
	while (number[z + i] != '\0')
	{
		if (z > 17 || !ft_isdigit(number[i + z++]))
			return (-1);
	}
	return (0);
}

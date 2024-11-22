/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:29:41 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/21 22:55:19 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** @brief check if the cmd init with a pipe */
int	check_init_pipe(char *cmd, int *error)
{
	int	i;

	i = 0;
	while (ft_isspace(cmd[i]))
		i++;
	if (cmd[i] == '|')
	{
		print_err("minishell: syntax error near unexpected token `|'");
		(*error) = 2;
		return (1);
	}
	return (0);
}

int	finderr_aux(char *cmd)
{
	if (cmd[0] == ';' || cmd[0] == '\\')
	{
		print_err("minishell: syntax error unexpected token");
		write(2, &cmd[0], 1);
		print_err("\n");
		return (3);
	}
	if (cmd[0] && (cmd[0] == '>' || cmd[0] == '<'))
	{
		if (cmd[1] == cmd[0] && cmd[2] == cmd[0])
		{
			print_err("minishell: error unexpected token '");
			write(2, &cmd[0], 1);
			print_err("'\n");
			return (2);
		}
	}
	return (0);
}

/** @brief check if have a command after pipe */
int	find_exe(char *cmd, int *i, int *error)
{
	int	j;

	j = *i + 1;
	while (cmd[j])
	{
		while (ft_isspace(cmd[j]))
			j++;
		if (cmd[j] == '|' || !cmd[j])
		{
			print_err ("minishell: syntax error near unexpected token `|'");
			(*error) = 2;
			return (1);
		}
		else
			break ;
	}
	if (j - *i == 1)
	{
		print_err ("minishell: syntax error near unexpected token `|'");
		(*error) = 2;
		return (1);
	}
	return (0);
}

/** @brief Check if the quote is open*/
int	is_quote_open(char *cmd, int *i, int *error)
{
	int	j;

	j = *i + 1;
	while (cmd[j])
	{
		if (cmd[j] == cmd[*i])
		{
			(*i) = j;
			return (0);
		}
		j++;
	}
	print_err ("minishell: syntax error - the quote is open\n");
	(*error) = 1;
	return (1);
}

int	check_cmds(char *cmd)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			is_quote_open(cmd, &i, &error);
		else if (cmd[i] == '\\' || cmd[i] == ';')
		{
			print_err ("minishell: syntax error\n");
			error = 1;
		}
		else if (finderr_aux(cmd + i))
			error = 2;
		if (error || check_init_pipe(cmd, &error) || check_isjoin(cmd, &error))
			return (error);
		i++;
	}
	return (error);
}

// int main(int argc, char *argv[])
// {
// 	char *line;
// 	(void) argc;
// 	while (1)
// 	{
// 		line = readline("minishell: ");
// 		if (check_cmds(line))
// 			printf("\033[31m - NOK! -\033[0m\n");
// 		else
// 			printf("The line is ok! \n");
// 	}
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:25:10 by pemirand          #+#    #+#             */
/*   Updated: 2024/11/22 17:17:37 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*	Export -> Imprime de forma ordenada - verificar se _ aparece depois das maiusculas ou antes, testar
*	Export df ed _d 3r 5r d3 -> cria todas as variáveis, vazias e dá erro da 3r, mas retorna sucesso
*	Export ff=dad=df -> cria variável ff = "dad=df"
*	Export ff+=dd -> adicona dd na variável já existente
*	Export ff=-df -> adiciona -df na variável
*/

int		order_print_stack(char **stack);
char	*export_check_var(char *var, int flag_print_error);

int	ft_export(t_main *pgr, int argc, char **argv)
{
	int		i;
	int		err_print_flag;
	char	*s;

	i = 1;
	err_print_flag = 1;
	if (argc == 1 && argv)
		order_print_stack(pgr->cur_envp);
	else if (argc > 1 && argv)
	{
		while (i < argc)
		{
			s = export_check_var(argv[i], err_print_flag);
			if (s == NULL)
				err_print_flag = 0;
			else
			{
				//Adiciona na env
				printf("%s\n", s);
				free(s);
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

char	*export_check_var(char *var, int flag_print_error)
{
	int		equal_pos;
	int		var_len;
	char	*var_name;

	var_len = ft_strlen(var);
	if (var_len <= 0)
		return (NULL);
	equal_pos = ft_str_char(var, '=');
	var_name = ft_substr(var, 0, equal_pos);
	if (isalpha(var[0]) || var[0] == '_')
	{
		if (var_len == equal_pos)
			return (free(var_name), ft_strjoin(var, "=''"));
		else
			return (free(var_name), ft_strdup(var));
	}
	else if (flag_print_error)
		print_error(SHELL_NAME, "not an identifier", var_name, NULL);
	return (free(var_name), NULL);
}

int	order_print_stack(char **stack)
{
	char	**dup_stack;
	int		s_len;

	if (!stack)
		return (EXIT_FAILURE);
	s_len = 0;
	while (stack[s_len])
		s_len++;
	dup_stack = matrix_dup(stack);
	dup_stack = ft_sort_char_tab(dup_stack, s_len);
	if (!dup_stack)
		return (EXIT_FAILURE);
	s_len = 0;
	while (dup_stack[s_len])
		ft_putendl_fd(dup_stack[s_len++], STDOUT_FILENO);
	free_matrix(dup_stack);
	return (EXIT_SUCCESS);
}



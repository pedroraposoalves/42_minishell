/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:25:10 by pemirand          #+#    #+#             */
/*   Updated: 2024/12/30 12:10:36 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
*	Export -> Imprime de forma ordenada - no linux _ aparece depois das maiusculas e antes das minúsculas
*	Export df ed _d 3r 5r d3 -> cria todas as variáveis, vazias e dá erro da 3r, mas retorna sucesso - check
*	Export ff=dad=df -> cria variável ff = 'dad=df' - check
*	Export ff+=dd -> adicona dd na variável já existente
*	Export ff=-df -> adiciona -df na variável - check
*	No env, não aparecem as vars vazias, no export sim
*	linux, expor imprimri sempre as vars entre ""
*/

int		order_print_stack(char **stack);
char	*export_check_var(char *var, int flag_print_error);
char	*add_quotes(char *s, int len, int start, int end);
int		ft_export_update_env(t_main *pgr, char *var_name, char *var);

int	ft_export(t_main *pgr, char **argv)
{
	int		i;
	int		err_print_flag;
	char	*var_name;
	int		argc;

	argc = matrix_len(argv);
	i = 1;
	err_print_flag = 1;
	if (argc == 1 && argv)
		order_print_stack(pgr->cur_envp);
	else if (argc > 1 && argv)
	{
		while (i < argc)
		{
			var_name = export_check_var(argv[i], err_print_flag);
			if (var_name == NULL)
				err_print_flag = 0;
			else
				ft_export_update_env(pgr, var_name, argv[i]);
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
		return (var_name);
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

char	*add_quotes(char *s, int len, int start, int end)
{
	char	*res;
	int		i;
	int		quotes;

	i = 0;
	quotes = 0;
	res = (char *)malloc(sizeof(char) * (len + 2));
	while (i < len + 2)
	{
		if (i == start || i == end)
		{
			res[i] = '"';
			quotes++;
		}
		else
			res[i] = s[i - quotes];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	ft_export_update_env(t_main *pgr, char *var_name, char *var)
{
	int		append_flag;
	char	*tmp1;
	char	*tmp2;

	if (var_name == NULL)
		return (EXIT_FAILURE);
	append_flag = 0;
	if (var_name[ft_strlen(var_name) - 1] == '+')
		append_flag = 1;
	if (append_flag == 0)
	{
		if (set_env_value(var_name, pgr, \
			&var[ft_strlen(var_name) + 1]) == EXIT_FAILURE)
		{
			append_env_value(var_name, pgr);
			set_env_value(var_name, pgr, &var[ft_strlen(var_name) + 1]);
		}
	}
	else
	{
		var_name[ft_strlen(var_name) - 1] = '\0';
		tmp1 = get_env_value(var_name, pgr);
		if (tmp1 == NULL)
		{
			append_env_value(var_name, pgr);
			set_env_value(var_name, pgr, &var[ft_strlen(var_name) + 2]);
		}
		else
		{
			tmp1 = ft_substr(tmp1, ft_strlen(var_name) \
					+ 1, ft_strlen(tmp1) - ft_strlen(var_name) - 1);
			tmp2 = ft_strjoin(tmp1, &var[ft_strlen(var_name) + 2]);
			set_env_value(var_name, pgr, tmp2);
			free(tmp1);
			free(tmp2);
		}
	}
	return (EXIT_SUCCESS);
}

	if (var_name == NULL)
		return (EXIT_FAILURE);
	append_flag = 0;
	if (var_name[ft_strlen(var_name) - 1] == '+')
		append_flag = 1;
	if (append_flag == 0)
	{
		if (set_env_value(var_name, pgr, \
			&var[ft_strlen(var_name) + 1]) == EXIT_FAILURE)
		{
			append_env_value(var_name, pgr);
			set_env_value(var_name, pgr, &var[ft_strlen(var_name) + 1]);
		}
	}
	else
	{
		var_name[ft_strlen(var_name) - 1] = '\0';
		tmp1 = get_env_value(var_name, pgr);
		if (tmp1 == NULL)
		{
			append_env_value(var_name, pgr);
			set_env_value(var_name, pgr, &var[ft_strlen(var_name) + 2]);
		}
		else
		{
			tmp1 = ft_substr(tmp1, ft_strlen(var_name) \
					+ 1, ft_strlen(tmp1) - ft_strlen(var_name) - 1);
			tmp2 = ft_strjoin(tmp1, &var[ft_strlen(var_name) + 2]);
			set_env_value(var_name, pgr, tmp2);
			free(tmp1);
			free(tmp2);
		}
	}
	return (EXIT_SUCCESS);
}

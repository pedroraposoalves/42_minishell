/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:23:03 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/10 20:12:59 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** @brief to handle with signal in here doc function
 * @param signal signal value*/
static void	here_signal(int signal)
{
	if (signal == SIGINT)
		exit(1);
}
/** @brief to handle with signal in here doc function when is in the child
 * @param signal signal value*/
static void	here_child_signal(int signal)
{
	if (signal == SIGINT)
		ft_putchar_fd('\n', 2);
}

/** @brief create and write here doc
 * @param dir dir and name of the file
 * @param delimiter*/
int	here_doc_file(char *file, t_token *token, char **envp)
{
	int		fd;
	int		flag;
	int		delimiter_len;
	char	*line;
	t_token	*delimiter;

	if (token->next->type == IS_SPACE)
		delimiter = token->next->next;
	else
		delimiter = token->next;
	delimiter_len = ft_strlen(delimiter->content) + 1;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, here_signal);
		line = readline(">");
		flag = strncmp(delimiter->content, line, delimiter_len);
		if (flag == 0)
			break ;
		if (delimiter->type != D_QUOTES && delimiter->type != S_QUOTES)
			set_envp_value(&line, envp, 0, 0);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	exit (EXIT_SUCCESS);
}

void	here_doc_exec(char *file, t_token *list, t_main *pgr)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == 0)
		here_doc_file(file, list, pgr->cur_envp);
	waitpid(pid, &g_exit, 0);
	if(WIFEXITED(g_exit))
		if(WEXITSTATUS(g_exit) == EXIT_SUCCESS)
		{
			list->type = REDIR_MQ;
			if (list->next->type == IS_SPACE)
				list = list->next->next;
			else
				list = list->next;
			free(list->content);
			list->content = file;
		}
}

void	here_doc(t_main *pgr)
{
	int		i;
	t_token	*tmp_list;
	char	*file;

	signal(SIGQUIT, here_child_signal);
	signal(SIGINT, here_child_signal);
	i = 0;
	tmp_list = pgr->tokens;
	while (tmp_list)
	{
		if (tmp_list->type == HERE_DOC)
		{
			file = ft_strjoin("/tmp/heredoc_", ft_itoa(i));
			here_doc_exec(file, tmp_list, pgr);
			i++;
		}
		tmp_list = tmp_list->next;
	}
}

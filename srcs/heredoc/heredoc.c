/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:23:03 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/20 13:27:23 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*find_delimiter(t_token *token)
{
	if (token->next->type == IS_SPACE)
		return (token->next->next);
	else
		return (token->next);
}

void	free_and_close_here_doc(char *line, int fd, char *delimiter, t_main *pgr)
{
	// t_main	*pgr;

	// pgr = NULL;
	// pgr = get_pgr(NULL);
	close (fd);
	if (!line)
	{
		printf ("%s warning: here-document at line 13 delimited by end-of-file (wanted %s')", SHELL_NAME, delimiter);
	}
	else
		free (line);
	if (pgr)
		free_all(pgr, pgr->root, 1);
	exit(EXIT_SUCCESS);
}

/** @brief create and write here doc
 * @param dir dir and name of the file
 * @param delimiter*/
void	here_doc_file(char *file, t_token *token, char **envp, t_main *pgr)
{
	int		fd;
	int		flag;
	int		delimiter_len;
	char	*line;
	t_token	*delimiter;

	set_heredoc_sig();
	delimiter = find_delimiter(token);
	delimiter_len = ft_strlen(delimiter->content) + 1;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	free(file);
	while (1)
	{
		line = readline(">");
		if (line)
			flag = ft_strncmp(delimiter->content, line, delimiter_len);
		if (!line || flag == 0)
			break ;
		if (delimiter->type != D_QUOTES && delimiter->type != S_QUOTES)
			set_envp_value(&line, envp, 0, 0);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free_and_close_here_doc(line, fd, delimiter->content, pgr);
}

void	here_doc_exec(char *file, t_token *list, t_main *pgr)
{
	pid_t	pid;

	ignore_signals();
	pid = fork();
	if (pid == 0)
		here_doc_file(file, list, pgr->cur_envp, pgr);
	waitpid(pid, &g_exit, 0);
	setup_signals();
	if (WIFEXITED(g_exit))
	{
		if (WEXITSTATUS(g_exit) == EXIT_SUCCESS)
		{
			list->type = REDIR_MQ;
			if (list->next->type == IS_SPACE)
				list = list->next->next;
			else
				list = list->next;
			free(list->content);
			list->content = file;
		}
		else
			free(file);
	}
}

void	here_doc(t_main *pgr)
{
	int		i;
	char	*n;
	t_token	*tmp_list;
	char	*file;

	i = 0;
	tmp_list = pgr->tokens;
	while (tmp_list)
	{
		if (tmp_list->type == HERE_DOC)
		{
			n = ft_itoa(i);
			file = ft_strjoin("/tmp/heredoc_", n);
			free(n);
			here_doc_exec(file, tmp_list, pgr);
			i++;
		}
		tmp_list = tmp_list->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:23:03 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/10 20:30:56 by pemirand         ###   ########.fr       */
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

	delimiter = find_delimiter(token);
	delimiter_len = ft_strlen(delimiter->content) + 1;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	while (1)
	{
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
	waitpid(pid, &global_exit, 0);
	if (WIFEXITED(global_exit))
	{
		if (WEXITSTATUS(global_exit) == EXIT_SUCCESS)
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
	else
		free(file);
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

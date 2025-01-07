/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:23:03 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/07 21:54:15 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** @brief to handle with signal in here doc function
 * @param signal signal value*/
static here_signal(int signal)
{
	if (signal == SIGINT)
		exit(1);
}

/** @brief to handle with signal in here doc function when is in the child
 * @param signal signal value*/
static here_signal(int signal)
{
	if (signal == SIGINT)
		ft_putchar_fd('\n', 2);
}

/** @brief create and write here doc
 * @param dir dir and name of the file
 * @param delimiter */
void *here_doc_file(char *dir, char *delimiter)
{
	int		fd;
	int		flag;
	int		delimiter_len;
	char	*line;

	delimiter_len = ft_strlen(delimiter) + 1;
	fd = open(dir, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	while (1)
	{
		line = readline(">");
		flag = strncmp(delimiter, line, delimiter_len);
		if (flag == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, '\n', 1);
		free(line);
	}
	free(line);
	close(fd);
	exit(EXIT_SUCCESS);
}

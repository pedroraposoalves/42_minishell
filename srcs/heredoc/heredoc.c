/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:23:03 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/09 13:20:30 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** @brief create and write here doc
 * @param dir dir and name of the file
 * @param delimiter */
int here_doc_file(char *file, t_token *token, char **envp)
{
    int     fd;
    int     flag;
    int     delimiter_len;
    char    *line;
    char    *delimiter;
    delimiter = token->next->next->content;
    delimiter_len = ft_strlen(delimiter) + 1;
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    while (1)
    {
        line = readline(">");
        flag = strncmp(delimiter, line, delimiter_len);
        if (flag == 0)
            break ;
        if (token->next->next->type != D_QUOTES \
            && token->next->next->type != S_QUOTES)
            set_envp_value(&line, envp, 0, 0);
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    free(line);
    close(fd);
    free(delimiter);
    token->next->next->content = file;
    token->type = REDIR_MQ;
    return (EXIT_SUCCESS);
}

int here_doc(t_main *pgr)
{
    int     i;
    t_token *tmp_list;
    char    *file;
    i = 0;
    tmp_list = pgr->tokens;
    while (tmp_list)
    {
        if(tmp_list->type == HERE_DOC)
        {
            file = ft_strjoin("/tmp/heredoc_", ft_itoa(i));
            if (here_doc_file(file, tmp_list, pgr->cur_envp) == EXIT_FAILURE)
                return (EXIT_FAILURE);
            else
                i++;
        }
        tmp_list = tmp_list->next;
    }
    return (EXIT_SUCCESS);
}

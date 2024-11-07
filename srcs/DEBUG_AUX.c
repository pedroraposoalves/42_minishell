#include "../minishell.h"

#define ORANGE  "\x1b[38;5;214m"
#define RED     "\x1b[31m"
#define BLUE    "\x1b[34m"
#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"


void	print_list(t_main *pgr)
{
	printf("----------------------------------------------------\n");
	printf("| %-13s | %-8s | %-10s | %-8s |\n", "token", "id", "len token", "type");
	printf("----------------------------------------------------\n");
	while (pgr->tokens)
	{
		printf("| %-13s | %-8i | %-10i | %-8i |\n",
			pgr->tokens->content,
			pgr->tokens->id,
			pgr->tokens->c_len,
			pgr->tokens->type);

		pgr->tokens = pgr->tokens->next;
	}
	printf("----------------------------------------------------\n");
}

#include <stdio.h>

void print_tree(void *root, int left, int right) {
   
    if (!root) return;
    int type = *((int *)root);
    int spacing = 5;  
  
    if (type == CMD) {
        t_exec *cmd_node = (t_exec *)root;
        printf("%*sCMD: ", left, "");
        for (int i = 0; cmd_node->args && cmd_node->args[i]; i++) {
            printf("%s ", cmd_node->args[i]);
        }
        printf("\n");
    }
    else if (type == REDIR || type == REDIR_MQ || type == APPEND || type == HERE_DOC) {
        t_redir *redir_node = (t_redir *)root;
        
        printf("%*sREDIR: %s\n", left, "", redir_node->file);
		printf("%*s|\n", left + spacing, "");
        print_tree(redir_node->next, left, right);
    }
    else if (type == PIPE) {
        t_pipe *pipe_node = (t_pipe *)root;        
        printf("%*sPIPE\n", left, "");
		printf("%*s/\n", left, "");
        print_tree(pipe_node->left, left - spacing, right);
		printf("%*s\\\n", left + spacing, "");
        print_tree(pipe_node->right, left + spacing, right);
    }
}














// //function used for debugging purposes
// void	print_exec(void *node, const char *prefix, int isLeft)
// {
// 	int			i;
// 	t_exec		*exec;
// 	const char	*str[] = {"CMD", "PIPE", "REDIR", "IS_SPACE",
// 		"S_QUOTES", "D_QUOTES", "APPEND", "HERE_DOC", "REDIR_MQ"};
// 	char		*arrow;
// 	if (isLeft)
// 		arrow = ft_strdup("├── ");
// 	else
// 		arrow = ft_strdup("└── ");
// 	exec = (t_exec *)node;
// 	printf("%s"RED"EXEC: Type = '%s' - %s\n"RESET,
// 		prefix,
// 		arrow,
// 		str[exec->type + 3]);
// 	free(arrow);
// 	i = -1;
// 	while (exec->args[++i])
// 		printf(BLUE"%s    %s\n"RESET, prefix, exec->args[i]);
// }
// void	print_redir(void *node, const char *prefix, int isLeft)
// {
// 	t_redir		*redir;
// 	char		new_prefix[256];
// 	const char	*str[] = {"GENERAL", "IN_QUOTE", "IN_DQUOTE", "WORD",
// 		"W_SPACE", "D_QUOTE", "S_QUOTE", "PIPE", "ENV", "RED_OUT",
// 		"D_R_OUT", "RED_IN", "HEREDOC", "FILE_NAME"};
// 	char		*arrow;
// 	if (isLeft)
// 		arrow = ft_strdup("├── ");
// 	else
// 		arrow = ft_strdup("└── ");
// 	redir = (t_redir *)node;
// 	printf("%s%s"ORANGE"%s: File Name = '%s'\n"RESET,
// 		prefix,
// 		arrow,
// 		str[redir->type + 3],
// 		redir->file);
// 	free(arrow);
// 	if (isLeft)
// 		snprintf(new_prefix, sizeof(new_prefix),
// 			"%s%s", prefix, "│   ");
// 	else
// 		snprintf(new_prefix, sizeof(new_prefix),
// 			"%s%s", prefix, "    ");
// 	print_tree(redir->next, new_prefix, 0);
// }
// void	print_pipe(void *node, const char *prefix, int isLeft)
// {
// 	t_pipe	*pipe;
// 	char	new_prefix_left[256];
// 	char	new_prefix_right[256];
// 	char	*arrow;
// 	pipe = (t_pipe *)node;
// 	if (isLeft)
// 		arrow = ft_strdup("├── ");
// 	else
// 		arrow = ft_strdup("└── ");
// 	printf("%s%sPIPE:\n", prefix, arrow);
// 	free(arrow);
// 	snprintf(new_prefix_left, sizeof(new_prefix_left), "%s│   ", prefix);
// 	snprintf(new_prefix_right, sizeof(new_prefix_right), "%s    ", prefix);
// 	print_tree(pipe->left, new_prefix_left, 1);
// 	print_tree(pipe->right, new_prefix_right, 0);
// }

// void	print_tree(void *node, const char *prefix, int isLeft)
// {
// 	int	type;
// 	if (!node)
// 		return ;
// 	type = *((int *)node);
// 	if (type == CMD)
// 		print_exec(node, prefix, isLeft);
// 	else if (type == REDIR || type == REDIR_MQ
// 		|| type == APPEND || type == HERE_DOC)
// 		print_redir(node, prefix, isLeft);
// 	else if (type == PIPE)
// 		print_pipe(node, prefix, isLeft);
// }
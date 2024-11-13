#include "../minishell.h"

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

void	print_tree(void *root, int left, int right)
{
	int	type;
	int	spacing;

	if (!root)
		return ;
	spacing = 5;
	type = *((int *)root);
	if (type == CMD)
	{
		t_exec	*cmd_node = (t_exec *)root;
		printf("%*sCMD: ", left, "");
		for (int i = 0; cmd_node->args && cmd_node->args[i]; i++)
			printf("%s ", cmd_node->args[i]);
		printf("\n");
	}
	else if (type == REDIR || type == REDIR_MQ || type == APPEND || type == HERE_DOC)
	{
		t_redir	*redir_node = (t_redir *)root;
		printf("%*s%s %s\n", left, "", (redir_node->type == APPEND)? "APPEND" : 
			(redir_node->type == HERE_DOC)? "HERE_DOC": 
			(redir_node->type == REDIR_MQ)? "REDIR_MQ": 
			"REDIR" , redir_node->file);
		printf("%*s|\n", left + spacing, "");
		print_tree(redir_node->next, left, right);
	}
	else if (type == PIPE)
	{
		t_pipe	*pipe_node = (t_pipe *)root;

		printf("%*sPIPE\n", left, "");
		printf("%*s/\n", left, "");
		print_tree(pipe_node->left, left - spacing, right);
		printf("%*s\\\n", left + spacing, "");
		print_tree(pipe_node->right, left + spacing, right);
	}
}

#include "minishell.h"
#include "parser/parser.h"


void print_tree(t_tree *root, int space) {
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print_tree(root->right, space);

    // Print current node after space count
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("->%s\n", root->node->cmd);

    // Process left child
    print_tree(root->left, space);
}

void display_tree(t_tree *root)
{
    print_tree(root, 0);
}

t_redir    *mimic_redirection(int type, char *file_name)
{
	t_redir *node;

	node = ft_malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->open_mode = O_TRUNC;
	node->file_name = file_name;
	node->type = type;
	node->next = NULL;
	return (node);
}

t_shell    *mimic_lexer(char *cmd, char *args, t_redir *redir, e_types cmd_type)
{
	t_shell *node;
	
	node = ft_malloc(sizeof(t_shell));
	if (!node)
		return (NULL);
	node->cmd = ft_strdup(cmd);
	node->args = ft_split(args, ' ');
	node->redirections = redir;
	node->cmd_type = cmd_type;
	return (node);
}

// void	mimic_tree(t_tree *root)
// {
// 	t_tree *tree;
	
// 	tree = ft_malloc(sizeof(t_tree));
// 	if (!tree)
// 		return ;
// 	tree = create_node(root->node->next); // pipe
// 	tree->left = create_node(root->node); // ls
// 	tree->right = create_node(root->node->next->next->next); // pipe
// 	tree->right->left = create_node(root->node->next->next); // cat
// 	tree->right->right = create_node(root->node->next->next->next->next); // grep
// 	display_tree(tree);
// }

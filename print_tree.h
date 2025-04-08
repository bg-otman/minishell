#include "minishell.h"

void        display_tree(t_tree *root);
t_redir    *mimic_redirection(int type, char *file_name);
t_shell    *mimic_lexer(char *cmd, char *args, t_redir *redir, e_types cmd_type);
void        mimic_tree(t_tree *root);
t_tree	*create_node(t_shell *node);

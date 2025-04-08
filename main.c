/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:43:29 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/08 10:48:12 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"
#include "print_tree.h"

t_shell	*get_commands()
{
	t_shell	*node;
	
	node = mimic_lexer("ls", "-l", NULL, T_COMMAND);
	node->next = mimic_lexer("|", " ", NULL, T_PIPE);
	node->next->next = mimic_lexer("cat", " ", mimic_redirection(OUTPUT_FILE, "out"), T_COMMAND);
	node->next->next->next = mimic_lexer("|", " ", NULL, T_PIPE);
	node->next->next->next->next = mimic_lexer("grep", "main.c", mimic_redirection(INPUT_FILE, "out"), T_COMMAND);
	node->next->next->next->next->next = mimic_lexer("|", " ", NULL, T_PIPE);
	node->next->next->next->next->next->next = mimic_lexer("echo", "Done", NULL, T_COMMAND);
	node->next->next->next->next->next->next->next = mimic_lexer("&&", " ", NULL, T_LOGICAL_OP);
	node->next->next->next->next->next->next->next->next = mimic_lexer("tr", "-d", NULL, T_COMMAND);
	
	node->next->next->next->next->next->next->next->next->next = mimic_lexer("|", " ", NULL, T_PIPE);
	node->next->next->next->next->next->next->next->next->next->next = mimic_lexer("cat", " ", NULL, T_COMMAND);
	
	node->next->next->next->next->next->next->next->next->next->next->next = mimic_lexer("||", " ", NULL, T_LOGICAL_OP);
	node->next->next->next->next->next->next->next->next->next->next->next->next = mimic_lexer("finish", " ", NULL, T_COMMAND);
	
	node->next->next->next->next->next->next->next->next->next->next->next->next->next = mimic_lexer("||", " ", NULL, T_LOGICAL_OP);
	node->next->next->next->next->next->next->next->next->next->next->next->next->next->next = mimic_lexer("last", " ", NULL, T_COMMAND);
	return (node);
}

void    start_shell(t_shell *tokens)
{
	char *line;

	t_tree *root;

	root = ft_malloc(sizeof(t_tree));
	if (!root)
		return ;
	while (true)
	{
		ft_bzero(tokens, sizeof(t_shell));
		line = readline(PROMPT);
		if (!ft_strcmp(line, "exit") || !line)
		{
			fdprintf(1, "exit\n");
			break ;
		}
		add_history(line);
		lexer(line, tokens);
		root = build_tree(tokens);
		printf("[%s]\n", root->node->cmd);
		display_tree(root);
		free(line);
	}
	free(line);
}

int main(int ac, char *av[], char *env[])
{
	(void) ac;
	(void) av;
	(void) env;
	t_shell *tokens;
	
	tokens = ft_malloc(sizeof(t_shell));
	if (!tokens)
		return 1;
	lexer("ls | cat", tokens);
	// printf("[%s]\n", get_commands()->cmd);
	// printf("[%s]\n", tokens->cmd);
	// start_shell(&tokens);
	
	t_tree *root = build_tree(tokens);
	printf("[%s]\n", root->node->cmd);
	
	free_garbage();
}


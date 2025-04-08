/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:43:29 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/08 17:23:24 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"

void    launch_shell(t_shell *tokens)
{
	t_tree *root;
	char *line;

	while (true)
	{
		line = readline(PROMPT);
		if (!ft_strcmp(line, "exit") || !line)
		{
			fdprintf(1, "exit\n");
			break ;
		}
		add_history(line);
		lexer(line, tokens);
		root = build_tree(tokens);
		print_tree(root, 0);
		free(line);
	}
	free(line);
}

int main(int ac, char *av[], char *env[])
{
	(void) ac;
	(void) av;
	(void) env;
	t_shell tokens;

	launch_shell(&tokens);
	 
	free_garbage();
}

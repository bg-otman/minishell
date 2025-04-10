/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:43:29 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/10 09:11:41 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_shell(t_shell *tokens)
{
	t_tree	*root;
	char	*line;
	int		exit_code;

	exit_code = 0;
	while (true)
	{
		line = readline(PROMPT);
		if (!ft_strcmp(line, "exit") || !line)
		{
			fdprintf(1, "exit\n");
			break ;
		}
		add_history(line);
		exit_code = lexer(line, tokens);
		if (exit_code)
			exit_code = 2;
		root = parser(tokens);
		print_tree(root, 0);
		free(line);
	}
	free(line);
}

int main()
{
	t_shell	tokens;
	
	launch_shell(&tokens);
	free_garbage();
	
	return (0);
}

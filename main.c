/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:43:29 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/16 16:55:06 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_shell(t_shell *tokens)
{
	t_tree	*root;
	char	*line;
	int		exit_code;
	pid_t	last_cpid;
	int		prev_pipe;
	
	exit_code = 0;
	prev_pipe = -1;
	while (TRUE)
	{
		if (!exit_code)
			line = readline(PROMPT);
		else
			line = readline(B_PROMPT);
		if (!ft_strcmp(line, "exit") || !line)
		{
			fdprintf(1, "exit\n");
			expander()->exit_code = exit_code;
			break ;
		}
		add_history(line);
		if (is_all_space(line))
			continue ;
		exit_code = lexer(line, tokens);
		if (exit_code)
		{
			exit_code = SYNTAX_ERROR;
			expander()->exit_code = exit_code;
			printf("exit_status [%d]\n", exit_code);
			continue;
		}
		root = parser(tokens);
		// print_tree(root, 0);
		last_cpid = execute_tree(root, prev_pipe, NULL, FALSE);
		exit_code =  wait_for_children(last_cpid);
		if (exit_code == -1)
			exit_code = expander()->exit_code;
		else
			expander()->exit_code = exit_code;
		printf("exit_status [%d]\n", exit_code);
		free(line);
	}
	rl_clear_history();
	free(line);
}

int main(int ac, char **av, char **env)
{
	t_shell	tokens;

	(void)ac;
	(void)av;
	expander()->env = env;
	add_env();
	launch_shell(&tokens);
	free_garbage();
	return (expander()->exit_code);
	return (0);
}


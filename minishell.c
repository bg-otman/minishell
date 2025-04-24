/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:43:29 by asajed           #+#    #+#             */
/*   Updated: 2025/04/22 21:21:22 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_readline(t_shell *tokens)
{
	char	*line;
	char	*tmp;

	if (!expander()->exit_code)
		line = readline(PROMPT);
	else
		line = readline(B_PROMPT);
	if (!line)
		exit_shell(NULL);
	tmp = line;
	line = ft_strdup(tmp);
	free(tmp);
	add_history(line);
	if (is_all_space(line))
		return (2);
	if (lexer(line, tokens))
	{
		expander()->exit_code = SYNTAX_ERROR;
		return (2);
	}
	return (0);
}

void	foo(int sig)
{
	if (sig == SIGINT && expander()->child == 0)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		expander()->exit_code = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		write(1, "\n", 1);
		expander()->exit_code = 130;
	}
}

void	handle_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, foo);
}

void	launch_shell(t_shell *tokens)
{
	t_tree	*root;
	int		exit_code;
	pid_t	last_cpid;
	int		prev_pipe;

	exit_code = 0;
	prev_pipe = -1;
	while (TRUE)
	{
		exit_code = ft_readline(tokens);
		if (exit_code == 2)
			continue ;
		root = parser(tokens);
		last_cpid = execute_tree(root);
		exit_code = wait_for_children(last_cpid);
		if (exit_code == -1)
			exit_code = expander()->exit_code;
		else
			expander()->exit_code = exit_code;
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	tokens;

	(void)ac;
	(void)av;
	handle_signals();
	expander()->env = env;
	add_env();
	launch_shell(&tokens);
}

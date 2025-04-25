/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:36:51 by asajed            #+#    #+#             */
/*   Updated: 2025/04/24 18:36:43 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_error(int err, char *arg)
{
	if (!expander()->pipe_exists)
		fdprintf(2, "exit\n");
	if (err == 1)
	{
		fdprintf(2, "minishell :exit: too many arguments\n");
		if (!expander()->pipe_exists)
			expander()->exit_code = 1;
		else
			exit(1);
	}
	else if (err == 2)
	{
		fdprintf(2,
			"minishell: exit: %s: numeric argument required\n", arg);
		exit(2);
	}
	return (0);
}

void	free_and_exit(int exit_code)
{
	rl_clear_history();
	free_garbage();
	if (!expander()->pipe_exists)
		fdprintf(2, "exit\n");
	exit(exit_code);
}

void	exit_shell(char **args)
{
	int (j), (i);
	if (!args || !args[1])
		free_and_exit(expander()->exit_code);
	j = 0;
	i = 1;
	if (args[1][j] == '+' || args[1][j] == '-')
		j++;
	while (args[i++])
		while (args[1][j])
			if (!ft_isdigit(args[1][j++]))
				print_error(2, args[1]);
	if (args && args[1] && args[2])
	{
		print_error(1, NULL);
		return ;
	}
	free_and_exit(ft_atoi(args[1]));
}

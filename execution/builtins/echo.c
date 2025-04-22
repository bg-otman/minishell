/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:58:54 by asajed            #+#    #+#             */
/*   Updated: 2025/04/17 15:26:54 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	options(char **args, int *i)
{
	int	j;
	int	nl;

	if (!ft_strcmp(args[0], "--"))
		return (1);
	j = 0;
	nl = 1;
	while (args[(*i)])
	{
		if (args[(*i)][0] != '-')
			return (nl);
		else
		{
			j = 1;
			while (args[(*i)][j] && args[(*i)][j] == 'n')
				j++;
			if (args[(*i)][j] || (!args[(*i)][j] && args[(*i)][j - 1] == '-'))
				return (nl);
			else
				nl = 0;
		}
		(*i)++;
	}
	return (nl);
}

void	execute_echo(char **args)
{
	int	i;
	int	nl;

	i = 1;
	if (!args[1])
	{
		fdprintf(1, "\n");
		exit(EXIT_SUCCESS);
	}
	nl = options(args, &i);
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
	exit(EXIT_SUCCESS);
}

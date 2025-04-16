/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:58:54 by asajed            #+#    #+#             */
/*   Updated: 2025/04/16 17:18:33 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	echo(char **args)
{
	int	i;
	int	nl;

	i = 1;
	if (!args[1])
		return (printf("\n"), 0);
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
	return (0);
}

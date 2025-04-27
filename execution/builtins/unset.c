/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 09:35:26 by asajed            #+#    #+#             */
/*   Updated: 2025/04/27 12:10:30 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_from_env(char *arg)
{
	int		i;
	int		j;
	char	**env;

	i = 0;
	j = 0;
	while (expander()->my_env[i]
		&& ft_strncmp(arg, expander()->my_env[i], ft_strlen(arg)))
		i++;
	if (expander()->my_env[i]
		&& !ft_strncmp(arg, expander()->my_env[i], ft_strlen(arg)))
	{
		j = 0;
		i = 0;
		env = expander()->my_env;
		while (env[i])
		{
			if (!ft_strncmp(arg, expander()->my_env[i], ft_strlen(arg)))
				i++;
			else if (expander()->my_env[i])
				expander()->my_env[j++] = env[i++];
		}
		env[j] = NULL;
	}
}

void	execute_unset(char **args)
{
	int	i;

	i = 1;
	if (args[i]
		&& (args[i][0] == '-' && (args[i][1] != '\0'
		&& ft_strcmp(args[i], "--"))))
	{
		fdprintf(2, "minishell: unset: no options allowed\n");
		exit(EXIT_FAILURE);
	}
	while (args[i])
	{
		if (!ft_strchr(args[i], '='))
			remove_from_env(args[i]);
		i++;
	}
}

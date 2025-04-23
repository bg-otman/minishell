/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:23:06 by asajed            #+#    #+#             */
/*   Updated: 2025/04/22 23:17:40 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_env(char **args)
{
	int	i;

	i = 0;
	if (args[1])
	{
		fdprintf(2, "No options or argument allowed\n");
		exit(EXIT_FAILURE);
	}
	while (expander()->my_env[i])
	{
		if (ft_strchr(expander()->my_env[i], '='))
		{
			if (!(!ft_strncmp("PATH=", expander()->my_env[i], 5)
					&& expander()->ignored))
				fdprintf(1, "%s\n", expander()->my_env[i++]);
			else
				i++;
		}
		else
			i++;
	}
	exit(EXIT_SUCCESS);
}

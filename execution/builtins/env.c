/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:23:06 by asajed            #+#    #+#             */
/*   Updated: 2025/04/17 15:28:36 by obouizi          ###   ########.fr       */
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
		printf("%s\n", expander()->my_env[i++]);
	exit(EXIT_SUCCESS);
}

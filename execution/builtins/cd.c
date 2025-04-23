/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:15 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/22 19:07:16 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_args(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

static int	cd_too_many_args(char **args)
{
	if (ft_strcmp(args[0], "--") != 0)
	{
		fdprintf(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

static int	cd_single_arg(char **args)
{
	if (args[0][0] == '-' && args[0][1] != '\0')
	{
		fdprintf(2, "minishell: cd: no options allowed\n");
		return (1);
	}
	if (chdir(args[0]) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

void	execute_cd(t_shell *cmd)
{
	char	**args;
	int		len;

	args = &cmd->args[1];
	len = count_args(args);
	expander()->exit_code = 1;
	if (len == 0)
	{
		fdprintf(2, "cd: please provide a relative or absolute path\n");
		return ;
	}
	if (len > 2)
	{
		fdprintf(2, "minishell: cd: too many arguments\n");
		return ;
	}
	if ((len == 2 && cd_too_many_args(args)) || (len == 1
			&& cd_single_arg(args)))
		return ;
	expander()->exit_code = 0;
}

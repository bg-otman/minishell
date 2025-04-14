/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:49:20 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/14 17:19:55 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_paths(t_shell *cmd, char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, cmd->cmd);
		if (access(tmp, F_OK) == 0)
		{
			cmd->is_exist = true;
			cmd->cmd = tmp;
			break ;
		}
		i++;
	}
}

void	get_cmd_path(t_shell *cmd)
{
	int		i;
	char	**env;
	char	**paths;

	i = 0;
	env = expander()->my_env;
	paths = NULL;
	if (!cmd->cmd)
		return ;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			paths = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (ft_search(cmd->cmd, '/'))
	{
		cmd->is_exist = true;
		return ;
	}
	check_paths(cmd, paths);
}

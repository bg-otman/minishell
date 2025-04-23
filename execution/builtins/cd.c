/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:15 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/17 17:09:57 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*handle_relative_path(char *target_path, char *curr_path)
{
	char	**parts;
	char	*tmp;
	char	*res;
	int		i;

	res = ft_strdup(curr_path);
	parts = ft_split(target_path, '/');
	i = 0;
	while (parts && parts[i])
	{
		if (!ft_strcmp(parts[i], ".."))
		{
			tmp = remove_last_dir(res);
			res = tmp;
		}
		else if (parts[i][0] != '\0' && ft_strcmp(parts[i], "."))
		{
			tmp = ft_strjoin(res, "/");
			res = ft_strjoin(tmp, parts[i]);
		}
		i++;
	}
	return (res);
}

void	update_env(char *new_path)
{
	char	**env;
	int		i;
	char	*tmp;

	i = 0;
	env = expander()->my_env;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			if (new_path[0] == '/')
			{
				update_old_pwd(&env[i][4]);
				env[i] = ft_strjoin("PWD=", new_path);
			}
			else
			{
				update_old_pwd(&env[i][4]);
				tmp = handle_relative_path(new_path, &env[i][4]);
				env[i] = ft_strjoin("PWD=", tmp);
			}
			return ;
		}
		i++;
	}
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
	update_env(args[0]);
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

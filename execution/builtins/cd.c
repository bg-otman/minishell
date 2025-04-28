/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:15 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/28 13:01:17 by obouizi          ###   ########.fr       */
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

char	*get_cwd(char *buf, int size, int old, char *path)
{
	if (!getcwd(buf, size) && old)
	{
		fdprintf(2, "cd: error retrieving current directory");
		perror(": getcwd: cannot access parent directories");
		return (get_env("PWD"));
	}
	else if (!getcwd(buf, size) && !old)
		return (ft_strjoin(ft_strjoin(get_env("PWD"), "/"), path));
	else if (old)
	{
		if ((!get_env("PWD") || !get_env("PWD")[0])
			&& expander()->pwd)
			return (expander()->pwd);
		return (get_env("PWD"));
	}
	return (getcwd(buf, size));
}

static int	cd_single_arg(char **args)
{
	char	buf[1024];
	t_env	env;

	expander()->pwd = getcwd(buf, sizeof(buf));
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
	ft_bzero(&env, sizeof(t_env));
	env.key = ft_strdup("OLDPWD");
	env.value = ft_strdup(get_cwd(buf, sizeof(buf), 1, args[0]));
	env.element = ft_strjoin(ft_strjoin(env.key, "="), env.value);
	add_to_env(&env);
	env.key = ft_strdup("PWD");
	env.value = ft_strdup(get_cwd(buf, sizeof(buf), 0, args[0]));
	env.element = ft_strjoin(ft_strjoin(env.key, "="), env.value);
	add_to_env(&env);
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

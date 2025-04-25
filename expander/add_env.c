/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:03:35 by asajed            #+#    #+#             */
/*   Updated: 2025/04/25 09:26:14 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_expander	*expander(void)
{
	static t_expander	exp = {0};

	return (&exp);
}

void	add_shell_level(void)
{
	t_expander	*shell;

	int (i), (j);
	shell = expander();
	i = 0;
	while (shell->my_env[i] && ft_strncmp("SHLVL=", shell->my_env[i], 6))
		i++;
	if (!shell->my_env[i])
		shell->my_env = add_to_array(shell->my_env, "SHLVL=1");
	else
	{
		j = ft_atoi(shell->my_env[i] + 6) + 1;
		if (j >= 1000)
		{
			fdprintf(2,
				"warning: shell level (%d) too high, resetting to 1", j);
			j = 1;
		}
		shell->my_env[i] = ft_strjoin("SHLVL=", ft_itoa(j));
	}
}

void	add_env(void)
{
	t_expander	*shell;
	char		buff[4096];
	int			i;

	i = 0;
	shell = expander();
	while (shell->env && shell->env[i])
		shell->my_env = add_to_array(shell->my_env, shell->env[i++]);
	if (!shell->my_env || (!shell->my_env[0]))
	{
		shell->ignored = 1;
		shell->my_env = add_to_array(shell->my_env, "OLDPWD");
		shell->my_env = add_to_array(shell->my_env, ft_strjoin("PWD=",
					getcwd(buff, sizeof(buff))));
		shell->my_env = add_to_array(shell->my_env, "SHLVL=1");
		shell->my_env = add_to_array(shell->my_env, "_=/usr/bin/env");
		shell->my_env = add_to_array(shell->my_env,
				ft_strjoin("PATH=/usr/local/sbin:/usr/local/bin:",
					"/usr/sbin:/usr/bin:/sbin:/bin"));
	}
	else
		add_shell_level();
}

char	*odd_quotes(char *env_value)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (env_value && env_value[i])
		if (((env_value[i] == '\"' || env_value[i] == '\'')
				&& env_value[i++]) || env_value[i++])
			j++;
	new = ft_malloc(ft_strlen(env_value) + j);
	j = 0;
	i = 0;
	while (env_value && env_value[i])
	{
		if (env_value[i] == '\"' || env_value[i] == '\'')
			new[j++] = '\\';
		new[j++] = env_value[i++];
	}
	new[j] = 0;
	return (new);
}

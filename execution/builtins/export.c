/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:26:12 by asajed            #+#    #+#             */
/*   Updated: 2025/04/22 23:18:12 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../expander/expander.h"

int	print_export(void)
{
	int (i), (j);
	i = 0;
	while (expander()->my_env[i])
	{
		if (!((!ft_strncmp("PATH=", expander()->my_env[i], 5)
					&& expander()->ignored)
				|| !ft_strncmp(expander()->my_env[i], "_=", 2)))
		{
			j = 0;
			if (expander()->my_env[i][j])
				fdprintf(1, "declare -x ");
			while (expander()->my_env[i][j] && expander()->my_env[i][j] != '=')
				fdprintf(1, "%c", expander()->my_env[i][j++]);
			if (ft_strchr(expander()->my_env[i], '='))
				fdprintf(1, "=\"%s\"",
					ft_strchr(expander()->my_env[i++], '=') + 1);
			else
				i++;
			fdprintf(1, "\n");
		}
		else
			i++;
	}
	exit(EXIT_SUCCESS);
}

void	add_to_env(t_env *env)
{
	int			i;
	t_expander	*a;

	i = 0;
	a = expander();
	if (!env->element)
		env->element = env->key;
	while (a->my_env[i])
	{
		if (!ft_strncmp(env->key, a->my_env[i], ft_strlen(env->key))
			&& (!a->my_env[i][ft_strlen(env->key)]
			|| a->my_env[i][ft_strlen(env->key)] == '=' ))
			break ;
		i++;
	}
	if (!a->my_env[i])
		a->my_env = add_to_array(a->my_env, env->element);
	else if (env->append)
	{
		if (!a->my_env[i][ft_strlen(env->key)])
			a->my_env[i] = ft_strjoin(a->my_env[i], "=");
		a->my_env[i] = ft_strjoin(a->my_env[i], env->value);
	}
	else if (!env->alone)
		a->my_env[i] = env->element;
}

int	parse_input(char *arg, t_env *env, char	*msg)
{
	int (i);
	i = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (fdprintf(2, "%s", msg), 1);
	while (arg[i] && arg[i] != '=')
	{
		if ((!ft_isalnum(arg[i]) && arg[i] != '+' && arg[i] != '_')
			|| (arg[i] == '+' && arg[i + 1] != '='))
			return (fdprintf(2, "%s", msg), 1);
		i++;
	}
	env->append = 1;
	if (!arg[i])
		env->alone = 1;
	if (arg[i - 1] == '+' && i--)
		env->append++;
	env->key = ft_substr(arg, 0, i);
	if (!env->alone)
	{
		env->value = ft_substr(arg, i + env->append, ft_strlen(arg));
		env->element = ft_strjoin(ft_strjoin(env->key, "="), env->value);
	}
	env->append--;
	return (0);
}

void	execute_export(char **args)
{
	t_env	env;
	char	*msg;

	int (i);
	i = 1;
	msg = ft_strjoin(ft_strjoin("minishell: export: `", args[i]),
			"' : not a valid identifier\n");
	expander()->exit_code = 0;
	if (!args[i])
		print_export();
	while (args[i])
	{
		ft_bzero(&env, sizeof(t_env));
		if (!parse_input(args[i], &env, msg))
		{
			if (!ft_strcmp(env.key, "PATH") && expander()->ignored)
				expander()->ignored = 0;
			add_to_env(&env);
		}
		else
			expander()->exit_code = 1;
		i++;
	}
}

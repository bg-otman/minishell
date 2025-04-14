/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:04:58 by asajed            #+#    #+#             */
/*   Updated: 2025/04/12 18:30:46 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*get_env(char *name)
{
	char		*env_value;
	char		*cmp;
	char		**my_env;
	int			i;

	i = 0;
	my_env = expander()->my_env;
	cmp = ft_strjoin(name, "=");
	while (my_env && my_env[i])
	{
		if (my_env[i] && !ft_strncmp(cmp, my_env[i], ft_strlen(cmp)))
		{
			env_value = ft_strdup(ft_strchr(my_env[i], '=') + 1);
			break ;
		}
		i++;
	}
	if (!my_env || !my_env[i])
		return (ft_strdup(""));
	ft_strdup(env_value);
	return (env_value);
}

char	*get_start(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (ft_substr(str, 0, i));
}

char	*get_var(char *str)
{
	int	i;
	int	start;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	start = i++;
	if (str[i] && str[i] == '{')
	{
		start++;
		i++;
	}
	while (str[i] && (str[i] != '\\' && str[i] != '\'' && str[i] != '$'
			&& str[i] != '/' && str[i] != '!' && str[i] != '\"'
			&& str[i] != ' '))
		i++;
	return (ft_substr(str, start + 1, i - start - 1));
}

char	*get_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	i++;
	while (str[i] && (str[i] != '\\' && str[i] != '\'' && str[i] != '$'
			&& str[i] != '/' && str[i] != '!' && str[i] != '\"'
			&& str[i] != ' '))
		i++;
	return (ft_substr(str, i, ft_strlen(str) - i));
}

int	expand_dollar(t_data *data, t_token *token)
{
	char	*env_value;
	char	*start;
	char	*end;
	char	*tmp;

	tmp = get_var(token->value);
	env_value = get_env(tmp);
	start = get_start(token->value);
	end = get_end(token->value);
	if (!end)
		return (1);
	tmp = ft_strjoin(start, env_value);
	env_value = ft_strjoin(tmp, end);
	if (!env_value || !env_value[0])
		return (remove_token(data->tokens, token), 0);
	if (token->state == DEFAULT)
		return (add_default(ft_split(env_value, ' '), token, data));
	else
		replace_word(env_value, token, data);
	return (0);
}

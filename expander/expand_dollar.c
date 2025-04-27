/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:04:58 by asajed            #+#    #+#             */
/*   Updated: 2025/04/27 12:07:17 by asajed           ###   ########.fr       */
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
	if (!ft_strcmp("?", name))
		return (ft_itoa(expander()->exit_code));
	if (!ft_strcmp("0", name))
		return (ft_strdup("minishell"));
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
	env_value = odd_quotes(env_value);
	return (env_value);
}

char	*get_var(char *str, int *i)
{
	int		start;
	int		j;

	start = (*i);
	j = (*i) + 1;
	if (ft_isdigit(str[j]) || str[j] == '?' || !ft_isalpha(str[j]))
	{
		(*i) += 2;
		return (ft_substr(str, start + 1, (*i) - start -1));
	}
	while (str[j++] && ft_isalnum(str[j]))
		;
	(*i) = j--;
	return (ft_substr(str, start + 1, (*i) - start - 1));
}

char	*add_to_string(char *str, char c, int *i, int *j)
{
	char	*new;

	new = ft_malloc(sizeof(char) * 2);
	new[0] = c;
	new[1] = 0;
	str = ft_strjoin(str, new);
	if (j)
		(*j)++;
	if (i)
		(*i)++;
	return (str);
}

char	*expand_token(char *value, int cat, t_state state)
{
	char	*new;

	int (i), (j);
	i = 0;
	j = 0;
	new = ft_strdup("");
	while (value[i])
	{
		while (value[i] && value[i] != '$')
			new = add_to_string(new, value[i], &i, &j);
		new[j] = 0;
		if (value[i] == '$' && ft_valid(value[i + 1]))
		{
			new = ft_strjoin(new, get_env(get_var(value, &i)));
			while (new[j++])
				;
		}
		else if (value[i] == '$' && !cat && !state && !value[i + 1])
			i++;
		else
			new = add_to_string(new, value[i], &i, &j);
	}
	return (new);
}

int	expand_dollar(t_data *data, t_token *token)
{
	char	*env_value;
	char	**values;

	env_value = expand_token(token->value, token->cat, token->state);
	if (!env_value || !env_value[0])
	{
		token->value = NULL;
		return (0);
	}
	if (token->state == DEFAULT)
	{
		values = ft_split(env_value, ' ');
		if (values[0] && !values[1])
		{
			token->value = values[0];
			return (0);
		}
		return (add_default(values, token, data));
	}
	else
		token->value = env_value;
	return (0);
}

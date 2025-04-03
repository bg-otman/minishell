/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:04:58 by asajed            #+#    #+#             */
/*   Updated: 2025/04/02 19:41:09 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*get_env(char *name, t_data *data)
{
	char	*env_value;

	if (ft_strlen(name) == 1 && name[0] == '?')
		env_value = ft_itoa(data->exit_code);
	else
	{
		env_value = getenv(name);
		if (!env_value)
			return (ft_strdup(""));
		env_value = ft_strdup(env_value);
	}
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
			&& str[i] != '/' && str[i] != '!' && str[i] != '}'))
		i++;
	return (ft_substr(str, start + 1, i - start - 1));
}

char	*get_end(char *str)
{
	int	i;
	int	brace;

	i = 0;
	brace = 0;
	while (str[i] && str[i] != '$')
		i++;
	i++;
	if (str[i] && str[i] == '{')
		brace = 1;
	while (str[i] && (str[i] != '\\' && str[i] != '\'' && str[i] != '$'
			&& str[i] != '/' && str[i] != '!' && str[i] != '}'))
		i++;
	if (str[i] == '}' && brace)
		i++;
	else if (brace)
		return (fdprintf(2, "minishell : parse error near '}'\n"), NULL);
	else if (str[i] == '}')
		return (fdprintf(2, "minishell : parse error near '{'\n"), NULL);
	return (ft_substr(str, i, ft_strlen(str) - i));
}

int	expand_dollar(t_data *data, t_token *token)
{
	char	*env_value;
	char	*start;
	char	*end;
	char	*tmp;

	tmp = get_var(token->value);
	env_value = get_env(tmp, data);
	start = get_start(token->value);
	end = get_end(token->value);
	if (!end)
		return (1);
	tmp = ft_strjoin(start, env_value);
	env_value = ft_strjoin(tmp, end);
	if (!env_value || !env_value[0])
		return (remove_token(data->tokens, token), 0);
	replace_word(env_value, token, data);
	return (0);
}

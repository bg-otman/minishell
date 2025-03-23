/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:05:58 by asajed            #+#    #+#             */
/*   Updated: 2025/03/22 23:17:23 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer.h"

int	same_string(char *line, int *i, char c)
{
	int	j;

	j = *i;
	if (c == ' ')
	{
		if (line[j] && !ft_whitespace(line[j]) && operator(line[j]) == 0)
			return (0);
		return (1);
	}
	if (line[j] == c)
		j++;
	if (line[j] && !ft_whitespace(line[j]) && operator(line[j]) == 0)
		return (0);
	return (1);
}

t_state	find_state(char c)
{
	if (c == '\'')
		return (SINGLE_QUOTE);
	else if (c == '\"')
		return (DOUBLE_QUOTE);
	else if (c == '>' || c == '<')
		return (REDIRECTION);
	else if (c == '(' || c == ')')
		return (PARENTHESIS);
	else if (c == '&')
		return (AND);
	else if (c == '|')
		return (OR);
	else
		return (DEFAULT);
}

void	the_lexer(char *line, t_data *data)
{
	t_state	state;
	int		i;

	i = 0;
	skip_whitespace(line, &i);
	while (line[i])
	{
		state = find_state(line[i]);
		if (state == DEFAULT)
			handle_word(data, line, &i);
		else if (state == SINGLE_QUOTE || state == DOUBLE_QUOTE)
			handle_quote(data, line, &i, line[i]);
		else if (state == REDIRECTION || state == AND || state == OR)
			handle_the_rest(data, line, &i, state);
		else if (state == PARENTHESIS)
			handle_parenthesis(data, line, &i);
		skip_whitespace(line, &i);
		if (data->error)
		{
			free_token(data->tokens);
			data->tokens = NULL;
			break ;
		}
	}
}

char	**list_to_array(t_data *data)
{
	char	**tokens;
	t_token	*tmp;

	int (len), (i);
	if (!data->tokens || !*data->tokens)
		return (NULL);
	i = 0;
	len = tokenlen(*data->tokens);
	tmp = *data->tokens;
	tokens = malloc((len + 1) * sizeof(char *));
	while (tmp)
	{
		tokens[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

void	lexer(char *line, t_shell *shell)
{
	t_data	data;
	int		i;

	ft_bzero(&data, sizeof(data));
	data.exit_code = shell->exit_code;
	the_lexer(line, &data);
	if (data.error || expand_tokens(&data))
	{
		data.exit_code = 1;
		free_token(data.tokens);
		data.tokens = NULL;
		shell->exit_code = data.exit_code;
		return ;
	}
	join_tokens(&data);
	shell->tokens = list_to_array(&data);
	i = 0;
	while (shell->tokens && shell->tokens[i])
	{
		fdprintf(1, "tokens : %s\n", shell->tokens[i]);
		i++;
	}
	free_token(data.tokens);
}

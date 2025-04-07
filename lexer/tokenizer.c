/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:06:19 by asajed            #+#    #+#             */
/*   Updated: 2025/04/07 21:01:18 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	count_operator(char *line, int i, char c)
{
	int	j;

	j = 0;
	while (line[i] && line[i] == c)
	{
		i++;
		j++;
	}
	return (j);
}

void	handle_the_rest(t_data *data, char *line, int *i, t_state state)
{
	char	c;
	char	*token;
	int		j;
	int		start;

	c = line[(*i)];
	j = count_operator(line, *i, c);
	start = *i;
	while (line[(*i)] && line[(*i)] == c)
		(*i)++;
	if (c == '&' && j == 1)
		j = 3;
	if (j > 2)
	{
		fdprintf(2, "minishell : parse error near '%c'\n", c);
		data->error = 1;
		return ;
	}
	token = ft_substr(line, start, (*i) - start);
	add_token(data, token, state, 1);
}

void	handle_parenthesis(t_data *data, char *line, int *i)
{
	char	c;
	char	*token;

	c = line[(*i)];
	if (c == ')')
		token = ft_strdup(")");
	else
		token = ft_strdup("(");
	(*i)++;
	add_token(data, token, PARENTHESIS, 1);
}

void	handle_word(t_data *data, char *line, int *i)
{
	char	*token;
	int		start;

	start = (*i);
	while (line[(*i)] && ft_whitespace(line[(*i)]))
		(*i)++;
	if (!line[(*i)])
		return ;
	while (line[(*i)] && !ft_whitespace(line[(*i)])
		&& find_state(line[(*i)]) == DEFAULT)
		(*i)++;
	token = ft_substr(line, start, (*i) - start);
	add_token(data, token, DEFAULT, same_string(line, i, ' '));
}

void	handle_quote(t_data *data, char *line, int *i, char quote_char)
{
	char	*token;
	int		start;
	t_state	state;

	if (quote_char == '\"')
		state = DOUBLE_QUOTE;
	else
		state = SINGLE_QUOTE;
	start = (*i);
	(*i)++;
	while (line[(*i)] && line[(*i)] != quote_char)
		(*i)++;
	if (line[(*i)] != quote_char)
	{
		fdprintf(2, "minishell : parse error near '%c'\n", quote_char);
		data->error = 1;
		return ;
	}
	token = ft_substr(line, start, (*i) - start + 1);
	add_token(data, token, state, same_string(line, i, quote_char));
	(*i)++;
}

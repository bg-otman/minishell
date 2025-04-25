/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:17:53 by asajed            #+#    #+#             */
/*   Updated: 2025/04/17 13:10:16 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	operator(char c)
{
	return (c == '>' || c == '<' || c == '|' || c == '&' || c == '('
		|| c == ')');
}

int	ft_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
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

void	add_token(t_data *data, char *value, t_state state, int cat)
{
	t_token	*tmp;
	t_token	*new_token;
	t_token	**tokens;

	tokens = data->tokens;
	new_token = (t_token *)ft_malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = value;
	new_token->state = state;
	new_token->cat = cat;
	new_token->next = NULL;
	if (!tokens)
	{
		tokens = (t_token **)ft_malloc(sizeof(t_token *));
		(*tokens) = new_token;
		data->tokens = tokens;
		return ;
	}
	tmp = (*tokens);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
	data->tokens = tokens;
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 07:59:06 by asajed            #+#    #+#             */
/*   Updated: 2025/04/17 13:15:03 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*add_group(t_token *token, t_shell **shell)
{
	t_token	*start;
	t_token	*end;
	int		i;

	i = 1;
	start = token;
	(*shell) = add_new_node(NULL);
	while (token)
	{
		if (token && !ft_strcmp("(", token->value))
		{
			i++;
			token = add_group(token->next, &(*shell)->group);
		}
		if (token && !ft_strcmp(")", token->value))
		{
			end = token;
			i--;
		}
		if (i == 0)
			return (set_group(start, end, (*shell)), token);
		if (token)
			token = token->next;
	}
	return (token);
}

void	remove_token(t_token **tokens, t_token *token)
{
	t_token	*tmp;
	t_token	*prev;

	if (!tokens || !*tokens)
		return ;
	tmp = *tokens;
	prev = NULL;
	while (tmp)
	{
		if (tmp == token)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*tokens = tmp->next;
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	token = NULL;
}

void	join_tokens(t_data *data)
{
	t_token	*tmp;
	t_token	**tokens;
	char	*value;

	tokens = data->tokens;
	if (!tokens || data->error)
		return ;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->cat == 0 && tmp->next)
		{
			if (!tmp->value)
				value = tmp->next->value;
			else
				value = ft_strjoin(tmp->value, tmp->next->value);
			tmp->value = value;
			tmp->cat = tmp->next->cat;
			remove_token(tokens, tmp->next);
		}
		else
			tmp = tmp->next;
	}
}

void	splitter(char *line, t_data *data)
{
	t_state	state;
	int		i;

	i = 0;
	while (line[i] && ft_whitespace(line[i]))
		i++;
	while (line[i])
	{
		state = find_state(line[i]);
		if (state == DEFAULT)
			handle_word(data, line, &i);
		else if (state == SINGLE_QUOTE || state == DOUBLE_QUOTE)
			handle_quote(data, line, &i, line[i]);
		else if (state == REDIRECTION || state == AND || state == OR)
			handle_the_rest(data, line, &i, state);
		else
			handle_parenthesis(data, line, &i);
		while (line[i] && ft_whitespace(line[i]))
			i++;
	}
}

int	lexer(char *line, t_shell *shell)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(shell, sizeof(t_shell));
	splitter(line, &data);
	if (!data.tokens || data.error)
		return (data.error);
	expand_tokens(&data);
	if (!data.tokens || data.error)
		return (data.error);
	join_tokens(&data);
	if (data.error)
		return (data.error);
	syntax_error(&data);
	if (data.error)
		return (data.error);
	set_list(*data.tokens, shell);
	get_types(shell);
	return (data.error);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:06:09 by asajed            #+#    #+#             */
/*   Updated: 2025/04/02 19:48:26 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	operator(char c)
{
	return (c == '>' || c == '<' || c == '|'
		|| c == '&' || c == '(' || c == ')');
}

int	ft_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	skip_whitespace(char *line, int *i)
{
	while (line[(*i)] && ft_whitespace(line[(*i)]))
		(*i)++;
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
	int		len;

	tokens = data->tokens;
	if (!tokens)
		return ;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->cat == 0 && tmp->next)
		{
			len = ft_strlen(tmp->value) + ft_strlen(tmp->next->value);
			value = ft_malloc(len + 1);
			ft_strlcpy(value, tmp->value, len + 1);
			ft_strlcat(value, tmp->next->value, len + 1);
			tmp->value = value;
			tmp->cat = tmp->next->cat;
			remove_token(tokens, tmp->next);
		}
		else
			tmp = tmp->next;
	}
}

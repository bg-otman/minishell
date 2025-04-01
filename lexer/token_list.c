/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:06:17 by asajed            #+#    #+#             */
/*   Updated: 2025/03/23 13:44:09 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	tokenlen(t_token *token)
{
	int	i;

	if (!token)
		return (0);
	i = 0;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}

void	replace_word(char *new, t_token *old, t_data *data)
{
	t_token	*tmp;
	t_token	**tokens;

	tokens = data->tokens;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp == old)
		{
			// free(tmp->value);
			tmp->value = new;
			return ;
		}
		tmp = tmp->next;
	}
	data->tokens = tokens;
}

void	free_token(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next;

	if (!tokens)
		return ;
	tmp = (*tokens);
	while (tmp)
	{
		next = tmp->next;
		// free(tmp->value);
		// free(tmp);
		tmp = next;
	}
	if (tokens)
		free(tokens);
	tokens = NULL;
}

t_token	*a_new_token(char *value, t_state state, int cat)
{
	t_token	*token;

	token = (t_token *)ft_malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->state = state;
	token->cat = cat;
	token->next = NULL;
	return (token);
}

void	add_token(t_data *data, char *value, t_state state, int cat)
{
	t_token	*tmp;
	t_token	*new_token;
	t_token	**tokens;

	tokens = data->tokens;
	new_token = a_new_token(value, state, cat);
	if (!new_token)
		return ;
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

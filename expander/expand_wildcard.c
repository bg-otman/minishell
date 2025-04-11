/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:00:15 by asajed            #+#    #+#             */
/*   Updated: 2025/04/11 18:48:39 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_wildcard(t_data *data)
{
	t_token	*tmp;

	tmp = *data->tokens;
	if (!tmp)
		return ;
}

int	add_default(char **new, t_token *old, t_data *data)
{
	int		i;
	t_token	*previous;
	t_token	*tmp;

	i = 0;
	previous = NULL;
	tmp = *(data->tokens);
	while (new[i])
		i++;
	while (tmp)
	{
		if (tmp == old)
		{
			if (previous && is_redirection(previous->value) && i > 1)
			{
				data->error = 1;
				fdprintf(2, "minishell: %s: ambiguous redirect\n", old->value);
				return (1);
			}
		}
		previous = tmp;
		tmp = tmp->next;
	}
	add_words(new, old, data);
	return (0);
}

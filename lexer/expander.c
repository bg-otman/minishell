/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:29:01 by asajed            #+#    #+#             */
/*   Updated: 2025/03/22 22:00:06 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	expand_tokens(t_data *data)
{
	t_token	*tmp;
	t_token	*previous;

	if (!data->tokens)
		return (0);
	previous = NULL;
	tmp = *(data->tokens);
	while (tmp)
	{
		if (ft_strchr(tmp->value, '$') && (tmp->state == DEFAULT
				|| tmp->state == DOUBLE_QUOTE) && ft_strlen(tmp->value) != 1)
		{
			if (expand_dollar(data, tmp))
				return (1);
			if (previous)
				tmp = previous->next;
			else
				tmp = (*(data->tokens));
			continue ;
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (0);
}

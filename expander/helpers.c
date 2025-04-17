/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:07:49 by asajed            #+#    #+#             */
/*   Updated: 2025/04/17 19:08:07 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	escaped_char(t_token *token)
{
	int		i;
	int		j;
	char	*new;
	char	*value;

	i = 0;
	j = 0;
	value = token->value;
	while (value && value[i])
		if ((value[i] == '\\' && value[i++]) || value[i++])
			j++;
	new = ft_malloc(ft_strlen(value) + j);
	j = 0;
	i = 0;
	while (value && value[i])
	{
		if (value[i] == '\\')
			new[j++] = '\\';
		new[j++] = value[i++];
	}
	new[j] = 0;
	token->value = new;
}

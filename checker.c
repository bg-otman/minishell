/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:44:17 by asajed            #+#    #+#             */
/*   Updated: 2025/04/07 18:15:16 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_redirection(char *token)
{
	return (!ft_strcmp(token, "<") || !ft_strcmp(token, "<<")
		|| !ft_strcmp(token, ">") || !ft_strcmp(token, ">>"));
}

int	is_operator(char *token)
{
	if (!token)
		return (0);
	if (!ft_strcmp(token, "|") || !ft_strcmp(token, ")") || !ft_strcmp(token,
			"(") || !ft_strcmp(token, "<") || !ft_strcmp(token, ">")
		|| !ft_strcmp(token, "<<") || !ft_strcmp(token, ">>")
		|| !ft_strcmp(token, "||") || !ft_strcmp(token, "&&"))
		return (1);
	return (0);
}

int	is_logical_op(char *token)
{
	return (!ft_strcmp(token, "&&") || !ft_strcmp(token, "||")
		|| !ft_strcmp(token, "|"));
}

int	is_valid_adjacent(char *token, char *next)
{
	return ((!ft_strcmp(token, "(") && !ft_strcmp(next, "("))
		|| (!ft_strcmp(token, ")") && !ft_strcmp(next, ")"))
		|| (!ft_strcmp(token, ")") && !ft_strcmp(next, "|"))
		|| (!ft_strcmp(token, "|") && !ft_strcmp(next, "("))
		|| (!ft_strcmp(token, ")") && is_redirection(next))
		|| (!ft_strcmp(token, ")") && is_logical_op(next))
		|| (!ft_strcmp(token, "&&") && !ft_strcmp(next, "("))
		|| (!ft_strcmp(token, "||") && !ft_strcmp(next, "("))
		|| (is_logical_op(token) && is_redirection(next)));
}

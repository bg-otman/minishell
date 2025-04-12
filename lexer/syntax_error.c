/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:22:06 by asajed            #+#    #+#             */
/*   Updated: 2025/04/11 17:28:02 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	set_group(t_token *start, t_token *end, t_shell *shell)
{
	t_token	*link;

	link = end->next;
	end->next = NULL;
	set_list(start, shell);
	get_types(shell);
	end->next = link;
}

int	syntax_parenthesis(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (token)
	{
		if (!ft_strcmp("(", token->value))
		{
			tmp = token;
			while (tmp && ft_strcmp(")", tmp->value))
				tmp = tmp->next;
			if (!tmp)
				return (fdprintf(2,
						"minishell: syntax error near unexpected token ')'\n"),
					1);
		}
		token = token->next;
	}
	return (0);
}

int	check_parenthesis(t_token *token)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = token;
	while (tmp)
	{
		if (!ft_strcmp(")", tmp->value))
			count--;
		else if (!ft_strcmp("(", tmp->value))
			count++;
		tmp = tmp->next;
	}
	tmp = token;
	while (tmp && ft_strcmp(")", tmp->value) && ft_strcmp("(", tmp->value))
		tmp = tmp->next;
	if (count < 0 || (tmp && !ft_strcmp(")", tmp->value)))
		return (fdprintf(2,
				"minishell: syntax error near unexpected token ')'\n"),
			1);
	if (!count)
		return (0);
	else
		return (fdprintf(2,
				"minishell: syntax error near unexpected token '('\n"), 1);
}

int	check_syntax(t_token *token, char *message)
{
	t_token	*tmp;

	tmp = token;
	if (!token)
		return (0);
	if (is_logical_op(tmp->value))
		return (fdprintf(1, "%s '%s'\n", message, tmp->value), 1);
	while (tmp->next)
	{
		if ((is_operator(tmp->value) && is_operator(tmp->next->value)
				&& !is_valid_adjacent(tmp->value, tmp->next->value))
			|| ((!ft_strcmp(")", tmp->value) && !is_operator(tmp->next->value))
				|| (!is_operator(tmp->value)
					&& !ft_strcmp("(", tmp->next->value))))
			return (fdprintf(1, "%s '%s'\n", message, tmp->next->value), 1);
		tmp = tmp->next;
	}
	if (is_logical_op(tmp->value) || is_redirection(tmp->value))
		return (fdprintf(1, "%s '%s'\n", message, tmp->value), 1);
	return (0);
}

void	syntax_error(t_data *data)
{
	if (data->error || !data->tokens)
		return ;
	if (check_parenthesis((*data->tokens))
		|| syntax_parenthesis((*data->tokens)))
	{
		data->error = 1;
		return ;
	}
	if (check_syntax((*data->tokens),
			ft_strdup("minishell: syntax error near unexpected token")))
	{
		data->error = 1;
		return ;
	}
}

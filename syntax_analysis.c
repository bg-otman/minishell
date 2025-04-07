/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:54:56 by asajed            #+#    #+#             */
/*   Updated: 2025/04/07 18:16:12 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	**add_to_array(char **arr, char *element)
{
	char	**new_arr;
	int		i;
	int		j;

	i = 0;
	while (arr && arr[i])
		i++;
	new_arr = ft_malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_arr[j] = ft_strdup(arr[j]);
		j++;
	}
	new_arr[j++] = ft_strdup(element);
	new_arr[j] = NULL;
	return (new_arr);
}

t_shell	*add_new_node(t_shell *shell)
{
	t_shell	*new;

	new = ft_malloc(sizeof(t_shell));
	ft_bzero(new, sizeof(t_shell));
	new->next = NULL;
	if (shell)
		shell->next = new;
	return (new);
}

void	get_types(t_shell *shell)
{
	while (shell)
	{
		if (shell->args)
		{
			shell->cmd = ft_strdup(shell->args[0]);
			shell->cmd_type = T_COMMAND;
		}
		else
		{
			if (!ft_strcmp(shell->cmd, "(") || !ft_strcmp(shell->cmd, "("))
				shell->cmd_type = T_PARENTHESIS;
			else if (!ft_strcmp(shell->cmd, "|"))
				shell->cmd_type = T_PIPE;
			else
				shell->cmd_type = T_LOGICAL_OP;
		}
		shell = shell->next;
	}
}

void	set_list(t_token *token, t_shell *shell)
{
	while (token)
	{
		while (token && !is_logical_op(token->value))
		{
			if (is_redirection(token->value))
				token = token->next;
			else if (ft_strcmp(token->value, ")") && ft_strcmp(token->value,
					"("))
				shell->args = add_to_array(shell->args, token->value);
			token = token->next;
		}
		if (token && (is_logical_op(token->value) || !ft_strcmp(token->value,
					")") || !ft_strcmp(token->value, "(")))
		{
			shell = add_new_node(shell);
			shell->cmd = token->value;
			token = token->next;
		}
		shell = add_new_node(shell);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:54:56 by asajed            #+#    #+#             */
/*   Updated: 2025/04/16 13:33:14 by obouizi          ###   ########.fr       */
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

t_redir	*new_redir(t_shell *shell)
{
	t_redir	*new;
	t_redir	*current;

	new = ft_malloc(sizeof(t_redir));
	current = shell->redirections;
	ft_bzero(new, sizeof(t_redir));
	if (!shell->redirections)
		shell->redirections = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (new);
}

void	get_file(t_shell *shell, t_token *token)
{
	t_redir	*new;

	new = new_redir(shell);
	new->file_name = token->next->value;
	if (!ft_strcmp(token->value, ">"))
	{
		new->open_mode = O_CREAT | O_WRONLY | O_TRUNC;
		new->type = OUTPUT_FILE;
	}
	if (!ft_strcmp(token->value, ">>"))
	{
		new->open_mode = O_APPEND | O_CREAT | O_WRONLY;
		new->type = OUTPUT_FILE;
	}
	if (!ft_strcmp(token->value, "<<"))
	{
		new->open_mode = O_RDONLY;
		new->type = HERE_DOC;
	}
	if (!ft_strcmp(token->value, "<"))
	{
		new->open_mode = O_RDONLY;
		new->type = INPUT_FILE;
	}
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
			if (!ft_strcmp(shell->cmd, "|"))
				shell->cmd_type = T_PIPE;
			else if (shell->group)
				shell->cmd_type = T_PARENTHESIS;
			else if (shell->redirections)
				shell->cmd_type = T_COMMAND;
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
			{
				get_file(shell, token);
				token = token->next;
			}
			else if (!ft_strcmp(token->value, "("))
				token = add_group(token->next, &shell->group);
			else if (ft_strcmp(token->value, ")"))
				shell->args = add_to_array(shell->args, token->value);
			if (token)
				token = token->next;
		}
		if (token && (is_logical_op(token->value)))
		{
			shell = add_new_node(shell);
			shell->cmd = token->value;
			token = token->next;
		}
		if (token)
			shell = add_new_node(shell);
	}
}

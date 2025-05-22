/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:46:14 by asajed            #+#    #+#             */
/*   Updated: 2025/05/21 16:20:23 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*remove_quotes(char *token)
{
	char	*str;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	if (!token || (!ft_strchr(token, '\'') && !ft_strchr(token, '\"')))
		return (token);
	str = ft_strdup(token);
	while (token[i])
	{
		if (!quote && (token[i] == '\'' || token[i] == '\"'))
			quote = token[i++];
		else if (quote && (token[i] == quote) && token[i++])
			quote = 0;
		else if (token[i] == '\\' && (token[i + 1] == '\"'
				|| token[i + 1] == '\'' || token[i + 1] == '\\') && i++)
			str[j++] = token[i++];
		else
			str[j++] = token[i++];
	}
	str[j] = '\0';
	return (ft_strdup(str));
}

void	finalize_tree(t_tree *root)
{
	t_redir	*redir;
	int		i;
	t_shell	*shell;

	if (!root)
		return ;
	finalize_tree(root->left);
	shell = root->node;
	while (shell)
	{
		redir = shell->redirections;
		while (redir)
		{
			redir->file_name = remove_quotes(redir->file_name);
			redir = redir->next;
		}
		i = 0;
		while (shell->args && shell->args[i++])
			shell->args[i - 1] = remove_quotes(shell->args[i - 1]);
		if (shell->args)
			shell->cmd = shell->args[0];
		shell = shell->next;
	}
	finalize_tree(root->right);
}

void	add_words(char **new, t_token *old, t_data *data)
{
	t_token	*tmp;
	t_token	*next;
	int		i;

	tmp = *(data->tokens);
	while (tmp)
	{
		if (tmp == old)
		{
			i = 1;
			next = tmp->next;
			tmp->value = new[0];
			tmp->next = NULL;
			while (new[i] && new[i + 1])
				add_token(data, new[i++], DEFAULT, 1);
			if (new[i])
				add_token(data, new[i], DEFAULT, tmp->cat);
			tmp->cat = 1;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = next;
			return ;
		}
		tmp = tmp->next;
	}
}

void	handle_odd_quotes(t_token *tmp)
{
	while (tmp)
	{
		if (tmp->value && (ft_strchr(tmp->value, '\\')
				&& (ft_strchr(tmp->value, '\'')
					|| ft_strchr(tmp->value, '\"'))))
			escaped_char(tmp);
		tmp = tmp->next;
	}
}

int	expand_tokens(t_data *data)
{
	t_token	*tmp;
	t_token	*next;

	if (!data->tokens)
		return (0);
	tmp = *(data->tokens);
	handle_odd_quotes(tmp);
	while (tmp)
	{
		next = tmp->next;
		if (!ft_strcmp("<<", tmp->value) && next)
			next = next->next;
		if (tmp->value && ft_strchr(tmp->value, '$') && (tmp->state == DEFAULT
				|| tmp->state == DOUBLE_QUOTE))
		{
			if (expand_dollar(data, tmp))
				return (1);
			tmp = next;
			continue ;
		}
		tmp = next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:07:49 by asajed            #+#    #+#             */
/*   Updated: 2025/04/24 15:24:42 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	ft_valid(int c)
{
	return (ft_isalnum(c) || c == '?');
}

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

pid_t	execute_sub(t_tree *root)
{
	pid_t	last_cpid;

	int (in_file), (out_file), (in), (out);
	in = dup(0);
	out = dup(1);
	get_redirections(root->node, &in_file, &out_file);
	root->node->redirections = NULL;
	last_cpid = execute_tree(root);
	if (in_file != -1)
		dup2(in, STDIN_FILENO);
	if (out_file != -1)
		dup2(out, STDOUT_FILENO);
	close_fd(in);
	close_fd(out);
	close_fd(in_file);
	close_fd(out_file);
	return (last_cpid);
}

void	group_redir(t_redir *redir, t_tree *root)
{
	t_redir	*head;

	if (!redir)
		return ;
	head = redir;
	if (root->node->cmd_type == T_LOGICAL_OP || root->node->cmd_type == T_PIPE)
		root->node->redirections = redir;
	else
	{
		while (redir->next)
			redir = redir->next;
		redir->next = root->node->redirections;
		root->node->redirections = head;
	}
}

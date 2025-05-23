/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:58:57 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/19 12:51:24 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*create_node(t_shell *node)
{
	t_tree	*root;

	root = ft_malloc(sizeof(t_tree));
	if (!root)
		return (NULL);
	root->node = node;
	root->left = NULL;
	root->right = NULL;
	return (root);
}

t_shell	*get_operator(t_shell *start_node, t_shell **previous_node)
{
	t_shell	*node;
	t_shell	*operator;
	t_shell	*prev;

	*previous_node = NULL;
	operator = NULL;
	prev = NULL;
	node = start_node;
	while (node)
	{
		if (node->cmd_type == T_LOGICAL_OP)
		{
			*previous_node = prev;
			operator = node;
		}
		else if (node->cmd_type == T_PIPE && !operator)
		{
			*previous_node = prev;
			operator = node;
		}
		prev = node;
		node = node->next;
	}
	return (operator);
}

/*
 * Builds a syntax tree from a linked list of commands.
 * Finds the last logical operator (or pipe if no logic op),
 * splits the list into left and right parts,
 * and recursively builds the tree.
 */
t_tree	*build_tree(t_shell *start_node)
{
	t_tree	*root;
	t_shell	*operator;
	t_shell	*previous_node;
	t_shell	*after_operator;

	if (!start_node)
		return (NULL);
	if (!start_node->next)
		return (create_node(start_node));
	operator = get_operator(start_node, &previous_node);
	if (!operator)
		return (create_node(start_node));
	root = create_node(operator);
	after_operator = operator->next;
	operator->next = NULL;
	if (previous_node && start_node != operator)
	{
		previous_node->next = NULL;
		root->left = build_tree(start_node);
	}
	if (after_operator)
		root->right = build_tree(after_operator);
	return (root);
}

static t_tree	*handle_parenthesis(t_tree *root)
{
	t_redir	*redir;

	if (!root)
		return (NULL);
	root->left = handle_parenthesis(root->left);
	if (root->node->cmd_type == T_PARENTHESIS)
	{
		redir = root->node->redirections;
		root = build_tree(root->node->group);
		group_redir(redir, root);
		root = handle_parenthesis(root);
	}
	root->right = handle_parenthesis(root->right);
	return (root);
}

t_tree	*parser(t_shell *tokens)
{
	t_tree	*root;

	root = build_tree(tokens);
	root = handle_parenthesis(root);
	finalize_tree(root);
	return (root);
}

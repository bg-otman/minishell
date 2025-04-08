/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:58:57 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/08 11:05:04 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../print_tree.h"

t_tree	*create_node(t_shell *node)
{
	t_tree *root;
	
	root = ft_malloc(sizeof(t_tree));
	if (!root)
		return NULL;
    if (!node)
    {
        printf("found one\n");
    }
	root->node = node;
	root->left = NULL;
	root->right = NULL;
	return (root);
}

t_shell *get_operator(t_shell *start_node, t_shell **previous_node)
{
    t_shell *node;
    t_shell *operator;
    t_shell *prev;

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
    return operator;
}

t_tree *build_tree(t_shell *start_node)
{
    t_tree *root;
    t_shell *operator;
    t_shell *previous_node;
    t_shell *temp;
    t_shell *after_operator;

    if (!start_node)
        return (NULL);
    if (!start_node->next)
        return (create_node(start_node));
    operator = get_operator(start_node, &previous_node);
    if (!operator)
        return (create_node(start_node));
    root = create_node(operator);
    after_operator = operator->next; // save link to right list after operator
    operator->next = NULL; // break the list temporary
    if (previous_node && start_node != operator)
    {
        temp = previous_node->next; // save link to operator
        previous_node->next = NULL; // break it
        root->left = build_tree(start_node);
        previous_node->next = temp; // restore link to operator 
    }
    operator->next = after_operator; // restore the saved list
    if (after_operator)
        root->right = build_tree(after_operator);
    return (root);
}

// t_tree *build_tree(t_shell *tokens)
// {
//     t_tree *root;
    
//     if (!tokens)
//         return (NULL);
//     root = create_tree(tokens);
//     return (root);
// }

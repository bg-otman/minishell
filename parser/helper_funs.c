/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:49:20 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/08 17:22:21 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// remove when done printing
void print_tree(t_tree *root, int space)
{
    if (root == NULL)
        return;

    space += 10;

    print_tree(root->right, space);

    for (int i = 10; i < space; i++)
        printf(" ");
    printf("->%s\n", root->node->cmd);

    print_tree(root->left, space);
}

// void display_tree(t_tree *root)
// {
//     print_tree(root, 0);
// }
//

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:49:20 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/13 14:45:38 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe(int *pipe)
{
	pipe[0] = -1;
	pipe[1] = -1;
}

int is_builtin(char *cmd)
{
    return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd")
        || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
        || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"));
}

void	close_fd(int fd)
{
	if (fd >= 3)
		close(fd);
}

void    clean_and_exit(const char *error)
{
    perror(error);
    free_garbage();
    exit(EXIT_FAILURE);
}

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

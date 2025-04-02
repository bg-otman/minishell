/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:58:57 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/02 14:37:25 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    print_args(t_tree *node)
{
    printf("cmd : {%s} args : ", node->cmd);
    for (size_t i = 0; node->args && node->args[i]; i++)
    {
        printf("%s ", node->args[i]);
    }
    printf("\n");
}

e_types get_token_type(char *str)
{
    if (!ft_strcmp(str, "|"))
        return (T_PIPE);
    else if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<")
        || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<<"))
        return (T_REDIRECTION);
    else if (!ft_strcmp(str, "&&") || !ft_strcmp(str, "||"))
        return (T_LOGICAL_OP);
    else if (!ft_strcmp(str, "(") || !ft_strcmp(str, ")"))
        return (T_PARENTHESIS);
    else
        return (T_COMMAND);
}


t_tree  *create_node(e_types type, char *cmd)
{
    t_tree *root;

    root = ft_malloc(sizeof(t_tree));
    if (!root)
        return (NULL);
    ft_bzero(root, sizeof(root));
    root->type = type;
    root->cmd = ft_strdup(cmd);
    if (!root->cmd)
    {
        perror("Allocation fail ");
        free_garbage();
        exit(1);
    }
    return (root);
}

// t_tree  *add_to_tree(t_tree *node)
// {
//     if (!node)
        
// }

char    **add_to_array(char **arr, char *element)
{
    char    **new_arr;
    int     i;
    int     j;

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

char    **set_args(char **args, char **tokens, int *i)
{
    e_types type;

    type = get_token_type(tokens[++(*i)]);
    while (type == T_COMMAND && tokens[(*i)])
    {
        args = add_to_array(args, tokens[*i]);
        type = get_token_type(tokens[++(*i)]);
    }
    return (args);
}

// t_tree  *handle_redirection(char **tokens, int *i)
// {
//     int j;
//     e_types current_type;
//     e_types next_type;
    
//     if (*i == 0)
//     {
//         if ()
//     }
    
// }

// void    parse_tokens(char **tokens)
// {
//     int     i;
//     e_types type;
//     t_tree  *node;

//     if (!tokens)
//         return ;
//     i = 0;
//     while (tokens[i])
//     {
//         type = get_token_type(tokens[i]);
//         if (type != T_REDIRECTION && type != T_PARENTHESIS)
//             node = create_node(type, tokens[i]);
//         if (type == T_COMMAND)
//             node->args = set_args(node->args, tokens, &i);
//         // else if (type == T_REDIRECTION)
//         //     // handle redirection
            
//         else
//             i++;
//         print_args(node);
        
//         // add_to_tree(node);
        
//     }
// }

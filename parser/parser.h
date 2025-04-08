/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:59:28 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/08 17:22:41 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

// void    parse_tokens(char **tokens);
t_tree	*build_tree(t_shell *nodee);
t_tree	*create_node(t_shell *node);
void    print_tree(t_tree *root, int space);

#endif

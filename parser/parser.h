/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:59:28 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/09 09:32:50 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

t_tree    *parser(t_shell *tokens);
t_tree	*create_node(t_shell *node);
void    print_tree(t_tree *root, int space);

#endif

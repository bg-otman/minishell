/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:59:28 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/05 09:55:26 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

// void    parse_tokens(char **tokens);
t_tree	*build_tree(t_shell *nodee);
t_tree	*create_node(t_shell *node);
void    put_error(const char *error_msg);

#endif

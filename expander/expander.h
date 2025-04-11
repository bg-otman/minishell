/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:51:11 by asajed            #+#    #+#             */
/*   Updated: 2025/04/11 11:47:46 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../minishell.h"
# include "../lexer/lexer.h"

int		expand_dollar(t_data *data, t_token *token);
void	remove_token(t_token **tokens, t_token *token);
void	replace_word(char *new, t_token *old, t_data *data);
void	add_words(char **new, t_token *old, t_data *data);

#endif
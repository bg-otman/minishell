/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:51:11 by asajed            #+#    #+#             */
/*   Updated: 2025/04/17 19:08:15 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../minishell.h"
# include "../lexer/lexer.h"

int		expand_dollar(t_data *data, t_token *token);
void	expand_wildcard(t_data *data);
void	remove_token(t_token **tokens, t_token *token);
void	add_words(char **new, t_token *old, t_data *data);
int		add_default(char **new, t_token *old, t_data *data);
char	**add_to_array(char **arr, char *element);
char	*odd_quotes(char *env_value);
char	*get_end(char *str);
char	*get_var(char *str);
char	*get_start(char *str);
char	*get_env(char *name);
void	escaped_char(t_token *token);

#endif
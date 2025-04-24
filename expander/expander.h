/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:51:11 by asajed            #+#    #+#             */
/*   Updated: 2025/04/23 23:54:33 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../minishell.h"
# include "../lexer/lexer.h"

int		expand_dollar(t_data *data, t_token *token);
void	remove_token(t_token **tokens, t_token *token, int ignore);
void	add_words(char **new_, t_token *old, t_data *data);
int		add_default(char **new_, t_token *old, t_data *data);
char	**add_to_array(char **arr, char *element);
char	*odd_quotes(char *env_value);
char	*expand_token(char *value, int cat, t_state state);
void	escaped_char(t_token *token);
int		ft_valid(int c);

#endif

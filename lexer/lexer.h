/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 08:10:31 by asajed            #+#    #+#             */
/*   Updated: 2025/04/23 23:54:42 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

typedef enum s_state
{
	DEFAULT,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	ESCAPE,
	REDIRECTION,
	PARENTHESIS,
	AND,
	OR,
	PIPE
}					t_state;

typedef struct s_token
{
	char			*value;
	t_state			state;
	int				cat;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	int				error;
	t_token			**tokens;
}					t_data;

int				ft_whitespace(char c);
int				is_valid_adjacent(char *token, char *next);
int				is_operator(char *token);
int				is_logical_op(char *token);
int				is_redirection(char *token);
int				operator(char c);
int				same_string(char *line, int *i, char quote_char);
t_state			find_state(char c);
void			add_token(t_data *data, char *value, t_state state,
					int cat);
void			syntax_error(t_data *data);
int				count_operator(char *line, int i, char c);
void			handle_the_rest(t_data *data, char *line, int *i,
					t_state state);
void			handle_parenthesis(t_data *data, char *line, int *i);
void			handle_word(t_data *data, char *line, int *i);
void			handle_quote(t_data *data, char *line, int *i,
					char quote_char);
void			set_list(t_token *token, t_shell *shell);
void			get_types(t_shell *shell);
t_shell			*add_new_node(t_shell *shell);
t_token			*add_group(t_token *token, t_shell **shell);
void			set_group(t_token *start, t_token *end, t_shell *shell);
int				expand_tokens(t_data *data);
void			expand_wildcard(t_data *data);

#endif
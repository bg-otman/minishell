/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:06:01 by asajed            #+#    #+#             */
/*   Updated: 2025/03/22 23:00:56 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../LIBFT/libft.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}						t_garbage;

typedef enum s_state
{
	DEFAULT,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	BACKSLASH,
	ESCAPE,
	REDIRECTION,
	PARENTHESIS,
	AND,
	OR,
	PIPE
}						t_state;

typedef struct s_token
{
	char				*value;
	t_state				state;
	int					cat;
	struct s_token		*next;
}						t_token;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_data
{
	char				**envp;
	int					error;
	int					exit_code;
	t_token				**tokens;
}						t_data;

int						ft_whitespace(char c);
void					add_token(t_data *data, char *value, t_state state,
							int cat);
void					handle_word(t_data *data, char *line, int *i);
void					handle_quote(t_data *data, char *line, int *i,
							char quote_char);
void					skip_whitespace(char *line, int *i);
void					the_lexer(char *line, t_data *data);
void					print_list(t_token **tokens);
int						same_string(char *line, int *i, char quote_char);
void					free_token(t_token **tokens);
void					join_tokens(t_data *data);
void					remove_token(t_token **tokens, t_token *token);
int						expand_tokens(t_data *data);
void					replace_word(char *new, t_token *old, t_data *data);
t_state					find_state(char c);
void					handle_the_rest(t_data *data, char *line, int *i,
							t_state state);
int						fdprintf(int fd, const char *str, ...);
void					handle_parenthesis(t_data *data, char *line, int *i);
int						expand_dollar(t_data *data, t_token *token);
int						operator(char c);
int						tokenlen(t_token *token);

#endif // LEXER_H
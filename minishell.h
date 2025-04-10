/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:48:13 by asajed            #+#    #+#             */
/*   Updated: 2025/04/10 09:11:25 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>

# define true 1
# define false 0
# define PROMPT "\x1B[35m\e[1mminishell ~ \x1B[0m"
# define INPUT_FILE 0
# define OUTPUT_FILE 1

typedef enum e_types
{
    T_COMMAND,
    T_PIPE,
    T_REDIRECTION,
    T_LOGICAL_OP,
    T_PARENTHESIS,
} e_types;

// LEXER
typedef struct  s_redirection
{
	int    type; // input or output
	int    open_mode;
	char   *file_name;
	struct s_redirection *next; // if a command has more than one redirection
} t_redir;

typedef struct s_shell
{
	char			**args;
	char			*cmd;
	t_redir			*redirections;
	struct s_shell	*next;
	struct s_shell	*group; // for parenthesis
	int				exit_code;
	e_types			cmd_type;
}       t_shell;

// PARSER
typedef struct s_tree
{
	t_shell			*node;
	struct s_tree   *left;
	struct s_tree   *right;
} t_tree;

// lexer
int			lexer(char *line, t_shell *shell);
// parser
t_tree		*parser(t_shell *tokens);
t_tree		*create_node(t_shell *node);
// helper functions
void		print_tree(t_tree *root, int space);
int			fdprintf(int fd, const char *str, ...);

#endif
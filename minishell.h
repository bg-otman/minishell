/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:48:13 by asajed            #+#    #+#             */
/*   Updated: 2025/04/03 14:12:45 by obouizi          ###   ########.fr       */
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
# include "ft_malloc/ft_malloc.h"
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include "parser/parser.h"

# define true 1
# define false 0
# define PROMPT "\x1B[32mminishell ~ \e[1m"
# define O_APPEND: 1024
# define O_TRUNC: 512
# define INPUT_FILE 0
# define OUTPUT_FILE 1

typedef enum e_types
{
    COMMAND,
    ARGUMENT,
    PIPE,
    REDIRECTION,
    FILENAME,
    LOGICAL_OP,
    PARENTHESIS,
} e_types;

// LEXER
typedef struct  s_redirection
{
	int    type; // input or output
	int    open_mode;
	char   *filename;
	struct s_redirection *next; // if a command has more than one redirection
} t_redir;

typedef struct s_shell
{
	char		**args;
	char		*cmd;
	t_redir		*redirections;
	e_types		cmd_type;
}       t_shell;

// PARSER
typedef struct s_tree
{
	// e_types         type;
	// char            *cmd;
	// char            **args;
	t_shell *node;
	struct s_tree   *left;
	struct s_tree   *right;
} t_tree;

// void    lexer(char *line, t_shell *shell);
int		fdprintf(int fd, const char *str, ...);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:48:13 by asajed            #+#    #+#             */
/*   Updated: 2025/04/13 17:07:30 by obouizi          ###   ########.fr       */
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
#include <sys/time.h>
#include <sys/resource.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>

# define true 1
# define false 0
# define PROMPT "🤖 \x1B[35m\e[1mminishell ▶️ \x1B[0m"
# define B_PROMPT "💀 \x1B[31m\e[1mminishell ▶️ \x1B[0m"
# define INPUT_FILE 0
# define OUTPUT_FILE 1
# define SYNTAX_ERROR 2

typedef enum e_types
{
    T_COMMAND,
    T_PIPE,
    T_REDIRECTION,
    T_LOGICAL_OP,
    T_PARENTHESIS,
} t_types;

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
	t_types			cmd_type;
}       t_shell;

// expander

typedef struct s_expander
{
	char	**env;
	char	**my_env;
	int		ignored;
	int		exit_code;
} t_expander;

// PARSER
typedef struct s_tree
{
	t_shell			*node;
	struct s_tree   *left;
	struct s_tree   *right;
} t_tree;

// lexer
int			lexer(char *line, t_shell *shell);
//expander
void		finalize_tree(t_tree *root);
void		add_env(void);
t_expander	*expander(void);
// parser
t_tree		*parser(t_shell *tokens);
t_tree		*create_node(t_shell *node);
// execution
pid_t   	execute_tree(t_tree *root, int prev_pipe, int *current_pipe, int is_last);
int			wait_for_children(pid_t last_cpid);
// helper functions
int			is_builtin(char *cmd);
int			fdprintf(int fd, const char *str, ...);
void		print_tree(t_tree *root, int space);
void		clean_and_exit(const char *error);
void		init_pipe(int *pipe);
void		close_fd(int fd);
void		clean_child_ressources(int prev_pipe, int *current_pipe);

#endif
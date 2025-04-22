/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:48:13 by asajed            #+#    #+#             */
/*   Updated: 2025/04/22 18:49:18 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include "execution/get_next_line/get_next_line.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define PROMPT "🤖 \x1B[32m\e[1mminishell ▶️ \x1B[0m"
# define B_PROMPT "💀 \x1B[31m\e[1mminishell ▶️ \x1B[0m"
# define INPUT_FILE 0
# define OUTPUT_FILE 1
# define SYNTAX_ERROR 2
# define HERE_DOC 3

typedef enum e_types
{
	T_COMMAND,
	T_PIPE,
	T_REDIRECTION,
	T_LOGICAL_OP,
	T_PARENTHESIS,
}					t_types;

// LEXER
typedef struct s_redirection
{
	int						type; // input or output
	int						open_mode;
	char					*file_name;
	int						expand;
	struct s_redirection	*next; // if a command has more than one redirection
}					t_redir;

typedef struct s_shell
{
	char			**args;
	char			*cmd;
	int				is_exist;
	t_redir			*redirections;
	struct s_shell	*next;
	struct s_shell	*group; // for parenthesis
	t_types			cmd_type;
}					t_shell;

// expander
typedef struct s_expander
{
	char			**env;
	char			**my_env;
	int				ignored;
	int				exit_code;
}					t_expander;

typedef struct s_env
{
	char		*element;
	char		*key;
	char		*value;
	int			alone;
	int			append;
}					t_env;

// PARSER
typedef struct s_tree
{
	t_shell			*node;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

// lexer
int					lexer(char *line, t_shell *shell);
//expander
void				finalize_tree(t_tree *root);
void				add_env(void);
t_expander			*expander(void);
char				*remove_quotes(char *token);
// parser
t_tree				*parser(t_shell *tokens);
t_tree				*create_node(t_shell *node);
void				group_redir(t_redir *redir, t_tree *root);
// execution
pid_t				execute_tree(t_tree *root, int prev_pipe, int *current_pipe,
						int is_last);
int					wait_for_children(pid_t last_cpid);
int					get_redirections(t_shell *cmd, int *in_file, int *out_file);
void				get_cmd_path(t_shell *cmd);
void				check_paths(t_shell *cmd, char **paths);
char				*handle_heredoc(char *lim);
char				*generate_tmp_name(void);
int					exec_builtin(t_shell *cmd);
void				execute_cd(t_shell *cmd);
void				execute_pwd(t_shell *cmd);
void				execute_echo(char **args);
void				execute_env(char **args);
void				execute_export(char **args);
void				execute_unset(char **args);
pid_t				execute_sub(t_tree *root, int prev_pipe,
						int *curr_pipe, int is_last);
void				exit_shell(char **args);
// helper functions
int					is_builtin(char *cmd);
int					fdprintf(int fd, const char *str, ...);
int					count_args(char **arr);
void				clean_and_exit(const char *error);
void				init_pipe(int *pipe);
void				close_fd(int fd);
void				clean_child_ressources(int prev_pipe, int *current_pipe);
void				get_exit_code(char *cmd);
char				*call_heredoc(t_redir *redir);
void				call_builtins(t_shell *cmd);

#endif
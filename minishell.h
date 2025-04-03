/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:48:13 by asajed            #+#    #+#             */
/*   Updated: 2025/04/02 19:35:29 by asajed           ###   ########.fr       */
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
# include <errno.h>
# include <dirent.h>


# define true 1
# define false 0
# define PROMPT "\x1B[32mminishell ~ \e[1m"

typedef enum e_types
{
    T_COMMAND,
    T_ARGUMENT,
    T_PIPE,
    T_REDIRECTION,
    T_FILENAME,
    T_LOGICAL_OP,
    T_PARENTHESIS,
} e_types;

typedef struct s_tree
{
    e_types         type;
    char            *cmd;
    char            **args;
    char            *input;
    char            *output;
    struct s_tree   *left;
    struct s_tree   *right;
} t_tree;

// lexer
typedef struct s_shell
{
	int     exit_code;
	char    **tokens;
}       t_shell;

void    lexer(char *line, t_shell *shell);
int		fdprintf(int fd, const char *str, ...);


#endif
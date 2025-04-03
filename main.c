/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:43:29 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/02 19:47:21 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// # include "parser/parser.h"

int main(int ac, char *av[], char *env[])
{
    (void) ac;
    (void) av;
    (void) env;
    
    char *line;

    t_shell tokens;
    ft_bzero(&tokens, sizeof(t_shell));
    
    while (true)
    {
        line = readline(PROMPT);
        if  (!line || !ft_strcmp(line, "exit"))
        {
            fdprintf(1, "exit");
            break ;
        }
        add_history(line);
        lexer(line, &tokens);
        free(line);
    }
    free(line);
    free_garbage();
}


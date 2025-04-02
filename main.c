/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:43:29 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/02 14:37:32 by obouizi          ###   ########.fr       */
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
        if  (!line)
        {
            perror("readline ");
            break ;
        }
        if (!ft_strcmp(line, "exit"))
            break ;
        add_history(line);
        lexer(line, &tokens);
        // parse_tokens(tokens.tokens);
        
        free(line);
    }
    free(line);

    free_garbage();
}


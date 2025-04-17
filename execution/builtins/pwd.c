/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:11:19 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/17 13:34:28 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    execute_pwd(t_shell *cmd)
{
    char    **env;
    int     i;
    
    if (cmd->args[1]
        && (cmd->args[1][0] == '-' && cmd->args[1][1] != '\0'))
    {
        fdprintf(2, "minishell: pwd: no options allowed\n");
        exit(EXIT_FAILURE);
    }
    i = 0;
    env = expander()->my_env;
    while (env[i])
    {
        if (!ft_strncmp(env[i], "PWD", 3))
        {
            fdprintf(1, "%s\n", &env[i][4]);
            exit(EXIT_SUCCESS);
        }
        i++;
    }
    exit(EXIT_FAILURE);
}

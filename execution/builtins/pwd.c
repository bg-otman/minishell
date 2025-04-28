/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:11:19 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/28 12:49:06 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_pwd(t_shell *cmd)
{
	char	buffer[1024];
	char	*pwd;

	(void)cmd;
	if (cmd->args[1] && (cmd->args[1][0] == '-' && (cmd->args[1][1] != '\0'
		&& ft_strcmp(cmd->args[1], "--"))))
	{
		fdprintf(2, "minishell: pwd: no options allowed\n");
		exit(EXIT_FAILURE);
	}
	pwd = getcwd(buffer, sizeof(buffer));
	if (!pwd)
		pwd = get_env("PWD");
	printf("%s\n", pwd);
	exit(EXIT_SUCCESS);
}

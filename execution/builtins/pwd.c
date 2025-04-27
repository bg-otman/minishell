/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:11:19 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/26 20:21:55 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_pwd(t_shell *cmd)
{
	char	**env;
	char	buffer[1024];
	char	*pwd;
	int		i;

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
	i = 0;
	env = expander()->my_env;
	exit(EXIT_SUCCESS);
}

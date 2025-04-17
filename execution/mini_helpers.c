/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:47:55 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/17 13:38:12 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pipe(int *pipe)
{
	pipe[0] = -1;
	pipe[1] = -1;
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (TRUE);
	else
		return (FALSE);
}

void	close_fd(int fd)
{
	if (fd >= 3)
		close(fd);
}

void	get_exit_code(char *cmd)
{
	if (errno == EACCES)
	{
		fdprintf(2, "minishell: %s: Permission denied\n", cmd);
		exit(126);
	}
	if (ft_search(cmd, '/'))
		fdprintf(2, "minishell: %s: No such file or directory\n", cmd);
	else
		fdprintf(2, "%s: command not found\n", cmd);
	exit(127);
}

void	clean_and_exit(const char *error)
{
	perror(error);
	free_garbage();
	exit(EXIT_FAILURE);
}

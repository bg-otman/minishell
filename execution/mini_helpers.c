/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:47:55 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/27 12:17:16 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || (!ft_strcmp(cmd, "exit")
			&& expander()->pipe_exists)
		|| !ft_strcmp(cmd, "unset"))
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
	struct stat	sb;

	if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		fdprintf(2, "minishell: %s: Is a directory\n", cmd);
		exit(126);
	}
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

void	get_cmd_path(t_shell *cmd)
{
	int		i;
	char	**env;
	char	**paths;

	i = 0;
	env = expander()->my_env;
	paths = NULL;
	if (!cmd->cmd)
		return ;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			paths = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (ft_search(cmd->cmd, '/'))
	{
		cmd->is_exist = TRUE;
		return ;
	}
	check_paths(cmd, paths);
}

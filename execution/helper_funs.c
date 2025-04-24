/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:49:20 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/24 15:37:21 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(t_shell *cmd)
{
	if (!ft_strcmp(cmd->cmd, "cd") || !ft_strcmp(cmd->cmd, "unset")
		|| (!ft_strcmp(cmd->cmd, "export") && (cmd->args[1]))
		|| !ft_strcmp(cmd->cmd, "exit"))
	{
		if (!ft_strcmp(cmd->cmd, "cd"))
			execute_cd(cmd);
		else if (!ft_strcmp(cmd->cmd, "unset"))
			execute_unset(cmd->args);
		else if (!ft_strcmp(cmd->cmd, "export"))
			execute_export(cmd->args);
		else
			exit_shell(cmd->args);
		return (-1);
	}
	return (0);
}

void	check_paths(t_shell *cmd, char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, cmd->cmd);
		if (access(tmp, F_OK) == 0)
		{
			cmd->is_exist = TRUE;
			cmd->cmd = tmp;
			break ;
		}
		i++;
	}
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

char	*generate_tmp_name(void)
{
	int		i;
	char	*num;
	char	*filename;
	char	*base;

	i = 1;
	base = "/tmp/.here_doc";
	while (TRUE)
	{
		num = ft_itoa(i);
		filename = ft_strjoin(base, num);
		if (access(filename, F_OK) != 0)
			return (filename);
		i++;
	}
}

char	*handle_heredoc(char *lim)
{
	char	*tmp;
	char	*warning_msg;
	char	*limiter;
	char	*here_doc_file;
	int		fd;

	expander()->child = 2;
	here_doc_file = ft_strdup(generate_tmp_name());
	warning_msg = "minishell: warning: here-document delimited by end-of-file";
	fd = open(here_doc_file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		clean_and_exit("open here_doc ");
	limiter = ft_strjoin(remove_quotes(lim), "\n");
	fdprintf(STDOUT_FILENO, "> ");
	tmp = get_next_line(STDIN_FILENO);
	while (tmp && ft_strcmp(tmp, limiter))
	{
		write(fd, tmp, ft_strlen(tmp));
		fdprintf(STDOUT_FILENO, "> ");
		tmp = get_next_line(STDIN_FILENO);
	}
	if (!tmp)
		fdprintf(STDOUT_FILENO, "\n%s (wanted `%s')\n", warning_msg, lim);
	close(fd);
	expander()->child = 0;
	return (here_doc_file);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:49:20 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/26 18:55:38 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander/expander.h"

int	exec_builtin(t_shell *cmd)
{
	if (!ft_strcmp(cmd->cmd, "cd") || !ft_strcmp(cmd->cmd, "unset")
		|| (!ft_strcmp(cmd->cmd, "export") && (cmd->args[1]))
		|| (!ft_strcmp(cmd->cmd, "exit") && !expander()->pipe_exists))
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

void	exec_heredoc_child(char *lim, char *here_doc_file, int expand)
{
	char	*tmp;
	char	*limiter;
	char	*warning_msg;
	int		fd;

	signal(SIGINT, SIG_DFL);
	warning_msg = "minishell: warning: here-document delimited by end-of-file";
	fd = open(here_doc_file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		clean_and_exit("open here_doc ");
	limiter = ft_strjoin(remove_quotes(lim), "\n");
	fdprintf(STDOUT_FILENO, "> ");
	tmp = get_next_line(STDIN_FILENO);
	while (tmp && ft_strcmp(tmp, limiter))
	{
		if (expand)
			tmp = expand_token(tmp, 1, 1);
		write(fd, tmp, ft_strlen(tmp));
		fdprintf(STDOUT_FILENO, "> ");
		tmp = get_next_line(STDIN_FILENO);
	}
	if (!tmp)
		fdprintf(STDOUT_FILENO, "\n%s (wanted `%s')\n", warning_msg, lim);
	close(fd);
	exit(EXIT_SUCCESS);
}

char	*handle_heredoc(char *lim, int expand)
{
	char	*here_doc_file;
	pid_t	pid;
	int		status;

	if (expander()->heredoc_err == 1)
		return (NULL);
	expander()->child = 2;
	here_doc_file = ft_strdup(generate_tmp_name());
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
		exec_heredoc_child(remove_quotes(lim), here_doc_file, expand);
	waitpid(pid, &status, 0);
	expander()->child = 0;
	if (!(WIFEXITED(status) && (WEXITSTATUS(status) == 0)))
	{
		expander()->heredoc_err = 1;
		unlink(here_doc_file);
		return (NULL);
	}
	return (here_doc_file);
}

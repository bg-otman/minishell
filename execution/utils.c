/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:58:41 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/24 19:34:06 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_for_children(pid_t last_cpid)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	status = 0;
	if (waitpid(last_cpid, &status, 0) == -1)
		return (expander()->exit_code);
	while (wait(NULL) > 0)
		;
	expander()->child = 0;
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		return (expander()->exit_code);
	return (exit_code);
}

void	clean_child_ressources(int in_file, int out_file)
{
	
	char **arr = expander()->fds;
	int i = 0;

	while (arr && arr[i])
	{
		close_fd(ft_atoi(arr[i]));
		i++;
	}
	close_fd(in_file);
	close_fd(out_file);
}

int	get_in_out_file(t_redir *redir, int *in_file, int *out_file)
{
	int (fd);
	fd = -1;
	while (redir)
	{
		fd = open(redir->file_name, redir->open_mode, 0666);
		if (fd == -1)
		{
			fdprintf(2, "minishell: %s: %s\n", redir->file_name,
				strerror(errno));
			return (1);
		}
		if (!redir->type)
		{
			close_fd(*in_file);
			*in_file = fd;
		}
		else
		{
			close_fd(*out_file);
			*out_file = fd;
		}
		redir = redir->next;
	}
	return (0);
}

int	get_redirections(t_shell *cmd, int *in_file, int *out_file)
{
	t_redir	*redir;

	*in_file = -1;
	*out_file = -1;
	if (!cmd->redirections)
		return (0);
	redir = cmd->redirections;
	if (get_in_out_file(redir, in_file, out_file))
		return (1);
	if (*in_file != -1 && dup2(*in_file, STDIN_FILENO) == -1)
		clean_and_exit("dup2");
	if (*out_file != -1 && dup2(*out_file, STDOUT_FILENO) == -1)
		clean_and_exit("dup2");
	return (0);
}

void	call_builtins(t_shell *cmd)
{
	if (!ft_strcmp(cmd->args[0], "pwd"))
		execute_pwd(cmd);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		execute_echo(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "env"))
		execute_env(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "export"))
		execute_export(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		execute_unset(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		exit_shell(cmd->args);
}

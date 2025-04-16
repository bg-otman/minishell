/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:58:41 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/16 19:16:46 by obouizi          ###   ########.fr       */
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
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	return (exit_code);
}

void	clean_child_ressources(int prev_pipe, int *current_pipe)
{
	close_fd(prev_pipe);
	if (current_pipe)
	{
		close_fd(current_pipe[0]);
		close_fd(current_pipe[1]);
	}
}

int	get_in_out_file(t_redir **redi, int type)
{
	t_redir	*redir;

	int (file), (prev);
	prev = -1;
	file = -1;
	redir = *redi;
	while (redir)
	{
		if (redir->type == type
			|| (type == INPUT_FILE && redir->type == HERE_DOC))
		{
			close_fd(prev);
			if (type == INPUT_FILE && redir->type == HERE_DOC)
				redir->file_name = call_heredoc(redir);
			file = open(redir->file_name, redir->open_mode, 0666);
			if (file == -1)
			{
				*redi = redir;
				return (-2);
			}
			prev = file;
		}
		redir = redir->next;
	}
	return (file);
}

int	get_redirections(t_shell *cmd, int *in_file, int *out_file)
{
	t_redir	*redir;

	if (!cmd->redirections)
	{
		*in_file = -1;
		*out_file = -1;
		return (0);
	}
	redir = cmd->redirections;
	*in_file = get_in_out_file(&redir, INPUT_FILE);
	if (*in_file == -2)
		return (fdprintf(2, "minishell: %s: No such file or directory\n",
				redir->file_name), 1);
	*out_file = get_in_out_file(&redir, OUTPUT_FILE);
	if (*out_file == -2)
		return (fdprintf(2, "minishell: %s: Permission denied\n",
				redir->file_name), 1);
	if (*in_file != -1 && dup2(*in_file, STDIN_FILENO) == -1)
		clean_and_exit("dup2");
	if (*out_file != -1 && dup2(*out_file, STDOUT_FILENO) == -1)
		clean_and_exit("dup2");
	return (0);
}

void	call_builtins(t_shell *cmd)
{
	// if (!ft_strcmp(cmd->cmd, "cd"))
	// 	execute_cd(cmd);
	(void) cmd;
}
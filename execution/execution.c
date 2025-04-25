/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:08:59 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/25 10:30:26 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	execute_command(t_shell *cmd)
{
	pid_t	process_id;

	int (in_file), (out_file);
	if (exec_builtin(cmd))
		return (-1);
	process_id = fork();
	if (process_id == -1)
		clean_and_exit("fork");
	expander()->child = 1;
	if (process_id == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		get_cmd_path(cmd);
		if (get_redirections(cmd, &in_file, &out_file))
			exit(EXIT_FAILURE);
		clean_child_ressources(in_file, out_file);
		if (!cmd->cmd)
			exit(EXIT_SUCCESS);
		if (is_builtin(cmd->args[0]))
			call_builtins(cmd);
		else if (cmd->is_exist)
			execve(cmd->cmd, cmd->args, expander()->my_env);
		get_exit_code(cmd->cmd);
	}
	return (process_id);
}

char	**track_fds(char **arr, int fd1, int fd2)
{
	arr = add_to_array(arr, ft_itoa(fd1));
	arr = add_to_array(arr, ft_itoa(fd2));
	return (arr);
}

pid_t	execute_pipe(t_tree *root)
{
	pid_t	last_cpid;
	int		pipe_fd[2];

	int (in), (out);
	expander()->pipe_exists = TRUE;
	if (pipe(pipe_fd) == -1)
		clean_and_exit("pipe");
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	expander()->fds = track_fds(expander()->fds, in, out);
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		clean_and_exit("dup2 error");
	close(pipe_fd[1]);
	expander()->fds = track_fds(expander()->fds, pipe_fd[0], pipe_fd[1]);
	execute_tree(root->left);
	dup2(out, STDOUT_FILENO);
	if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
		clean_and_exit("dup2 error");
	close(pipe_fd[0]);
	last_cpid = execute_tree(root->right);
	dup2(in, STDIN_FILENO);
	close(in);
	close(out);
	expander()->pipe_exists = FALSE;
	return (last_cpid);
}

pid_t	execute_logical_op(t_tree *root)
{
	pid_t	last_cpid;

	last_cpid = -1;
	if (!ft_strcmp(root->node->cmd, "&&"))
	{
		last_cpid = execute_tree(root->left);
		expander()->exit_code = wait_for_children(last_cpid);
		if (expander()->exit_code == 0)
			last_cpid = execute_tree(root->right);
	}
	else
	{
		last_cpid = execute_tree(root->left);
		expander()->exit_code = wait_for_children(last_cpid);
		if (expander()->exit_code != 0)
			last_cpid = execute_tree(root->right);
	}
	return (last_cpid);
}

pid_t	execute_tree(t_tree *root)
{
	pid_t	last_cpid;

	last_cpid = -1;
	if (!root)
		return (-1);
	if ((root->node->cmd_type == T_LOGICAL_OP || root->node->cmd_type == T_PIPE)
		&& root->node->redirections)
		execute_sub(root);
	else if (root->node->cmd_type == T_PIPE)
		last_cpid = execute_pipe(root);
	else if (root->node->cmd_type == T_COMMAND)
		return (execute_command(root->node));
	else if (root->node->cmd_type == T_LOGICAL_OP)
		last_cpid = execute_logical_op(root);
	return (last_cpid);
}

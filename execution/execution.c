/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:08:59 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/22 18:49:48 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_command(t_shell *cmd, int prev_pipe, int *current_pipe,
		int is_last_cmd)
{
	int (in_file), (out_file);
	get_cmd_path(cmd);
	if (get_redirections(cmd, &in_file, &out_file))
		(clean_child_ressources(prev_pipe, current_pipe), exit(EXIT_FAILURE));
	if (in_file == -1 && prev_pipe != -1 && cmd->is_exist)
		if (dup2(prev_pipe, STDIN_FILENO) == -1)
			clean_and_exit("dup2");
	if (out_file == -1 && cmd->is_exist && !is_last_cmd && current_pipe
		&& current_pipe[1] != -1)
		if (dup2(current_pipe[1], STDOUT_FILENO) == -1)
			clean_and_exit("dup2");
	clean_child_ressources(prev_pipe, current_pipe);
	close_fd(in_file);
	close_fd(out_file);
	if (!cmd->cmd)
		exit(EXIT_SUCCESS);
	if (is_builtin(cmd->args[0]))
		call_builtins(cmd);
	else if (cmd->is_exist)
		execve(cmd->cmd, cmd->args, expander()->my_env);
	get_exit_code(cmd->cmd);
}

pid_t	process_command(t_shell *cmd, int prev_pipe, int *current_pipe,
		int is_last_cmd)
{
	pid_t	process_id;

	if (exec_builtin(cmd))
		return (-1);
	process_id = fork();
	if (process_id == -1)
		clean_and_exit("fork");
	if (process_id == 0)
		execute_command(cmd, prev_pipe, current_pipe, is_last_cmd);
	else
	{
		if (current_pipe)
			close_fd(current_pipe[1]);
		if (!is_last_cmd)
			close_fd(prev_pipe);
	}
	return (process_id);
}

pid_t	execute_pipe(t_tree *root, int *current_pipe, int prev_pipe,
		int *is_last)
{
	pid_t	last_cpid;

	if (pipe(current_pipe) == -1)
		clean_and_exit("pipe");
	*is_last = FALSE;
	execute_tree(root->left, prev_pipe, current_pipe, *is_last);
	prev_pipe = current_pipe[0];
	if (root->right && root->right->node->cmd_type == T_COMMAND)
		*is_last = TRUE;
	last_cpid = execute_tree(root->right, prev_pipe, current_pipe, *is_last);
	close_fd(prev_pipe);
	return (last_cpid);
}

pid_t	execute_logical_op(t_tree *root, int *current_pipe, int prev_pipe,
		int *is_last)
{
	pid_t	last_cpid;

	last_cpid = -1;
	if (!ft_strcmp(root->node->cmd, "&&"))
	{
		last_cpid = execute_tree(root->left, prev_pipe, current_pipe, *is_last);
		expander()->exit_code = wait_for_children(last_cpid);
		if (expander()->exit_code == 0)
			last_cpid = execute_tree(root->right, prev_pipe, current_pipe,
					*is_last);
	}
	else
	{
		last_cpid = execute_tree(root->left, prev_pipe, current_pipe, *is_last);
		expander()->exit_code = wait_for_children(last_cpid);
		if (expander()->exit_code != 0)
			last_cpid = execute_tree(root->right, prev_pipe, current_pipe,
					*is_last);
	}
	return (last_cpid);
}

pid_t	execute_tree(t_tree *root, int prev_pipe, int *curr_pipe, int is_last)
{
	int		current_pipe[2];
	pid_t	last_cpid;

	init_pipe(current_pipe);
	last_cpid = -1;
	if (!root)
		return (-1);
	if ((root->node->cmd_type == T_LOGICAL_OP || root->node->cmd_type == T_PIPE)
		&& root->node->redirections)
		execute_sub(root, prev_pipe, curr_pipe, is_last);
	else if (root->node->cmd_type == T_PIPE)
	{
		last_cpid = execute_pipe(root, current_pipe, prev_pipe, &is_last);
		close_fd(prev_pipe);
		close_fd(current_pipe[1]);
	}
	else if (root->node->cmd_type == T_COMMAND)
		return (process_command(root->node, prev_pipe, curr_pipe, is_last));
	else if (root->node->cmd_type == T_LOGICAL_OP)
		last_cpid = execute_logical_op(root, current_pipe, prev_pipe, &is_last);
	return (last_cpid);
}

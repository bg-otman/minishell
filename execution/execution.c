/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:08:59 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/14 11:35:01 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	verify_cmd(t_shell *cmd) // get path and verify cmd is exist
// {
	
// }

void	execute_command(t_shell *cmd, int prev_pipe, int *current_pipe,
		int is_last_cmd)
{
	int	in_file;
	int	out_file;

	in_file = -1;
	out_file = -1;
	// get_redirections(cmd, &in_file, &out_file);
	if (in_file != -1)
	{
		if (dup2(in_file, STDIN_FILENO) == -1)
			clean_and_exit("dup2");
	}
	else if (prev_pipe != -1)
		if (dup2(prev_pipe, STDIN_FILENO) == -1)
			clean_and_exit("dup2");
	if (out_file != -1)
	{
		if (dup2(out_file, STDOUT_FILENO) == -1)
			clean_and_exit("dup2");
	}
	else if (!is_last_cmd && current_pipe && current_pipe[1] != -1)
		if (dup2(current_pipe[1], STDOUT_FILENO) == -1)
			clean_and_exit("dup2");
	clean_child_ressources(prev_pipe, current_pipe);
	if (execve(ft_strjoin("/bin/", cmd->cmd), cmd->args, NULL) == -1)
		clean_and_exit("execve");
}

pid_t	process_command(t_shell *cmd, int prev_pipe, int *current_pipe,
		int is_last_cmd)
{
	pid_t	process_id;

	process_id = fork();
	if (process_id == -1)
		clean_and_exit("fork");
	if (process_id == 0)
		execute_command(cmd, prev_pipe, current_pipe, is_last_cmd);
	else
	{
		if (current_pipe)
			close_fd(current_pipe[1]);
	}
	return (process_id);
}

pid_t	execute_pipe(t_tree *root, int *current_pipe, int prev_pipe, int *is_last)
{
	pid_t	last_cpid;

	if (pipe(current_pipe) == -1)
		clean_and_exit("pipe");
	*is_last = false;
	execute_tree(root->left, prev_pipe, current_pipe, *is_last);
	prev_pipe = current_pipe[0];
	if (root->right && root->right->node->cmd_type == T_COMMAND)
		*is_last = true;
	last_cpid = execute_tree(root->right, prev_pipe, current_pipe, *is_last);
	return (last_cpid);
}

pid_t	execute_logical_op(t_tree *root, int *current_pipe, int prev_pipe, int *is_last)
{
	pid_t	last_cpid;
	int		exit_code;
	
	last_cpid = -1;
	if (!ft_strcmp(root->node->cmd, "&&"))
	{
		last_cpid = execute_tree(root->left, prev_pipe, current_pipe, *is_last);
		exit_code = wait_for_children(last_cpid);
		if (exit_code == 0)
			last_cpid = execute_tree(root->right, prev_pipe, current_pipe, *is_last);
	}
	else
	{
		last_cpid = execute_tree(root->left, prev_pipe, current_pipe, *is_last);
		exit_code = wait_for_children(last_cpid);
		if (exit_code != 0)
			last_cpid = execute_tree(root->right, prev_pipe, current_pipe, *is_last);	
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
	if (root->node->cmd_type == T_PIPE)
	{
		last_cpid = execute_pipe(root, current_pipe, prev_pipe, &is_last);
		close_fd(prev_pipe);
	}
	else if (root->node->cmd_type == T_COMMAND)
		return (process_command(root->node, prev_pipe, curr_pipe, is_last));
	else if (root->node->cmd_type == T_LOGICAL_OP)
		last_cpid = execute_logical_op(root, current_pipe, prev_pipe, &is_last);
	return (last_cpid);
}

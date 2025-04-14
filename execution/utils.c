/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:58:41 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/13 17:09:39 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int wait_for_children(pid_t last_cpid)
{
	int		status;
	int		exit_code;
	
	exit_code = 0;
	waitpid(last_cpid, &status, 0);
	while (wait(NULL) > 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	return (exit_code);
}

void    clean_child_ressources(int prev_pipe, int *current_pipe)
{
	close_fd(prev_pipe);
	if (current_pipe)
	{
		close_fd(current_pipe[0]);
		close_fd(current_pipe[1]);
	}
}

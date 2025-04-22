/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:52:42 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/21 11:19:36 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line/get_next_line.h"
# include "../../Libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	char	**paths;
	char	**cmd;
	char	**env;
	char	*limiter;
	int		pipe[2];
	int		fd_infile;
	int		fd_outfile;
	int		invalid_infile;
	int		here_doc;
	int		exist_cmd;
	int		cmds_num;
	int		exit_status;
}			t_data;

void		verify_cmd(t_data *data, char *cmd);
void		get_execs_paths(t_data *data, char *envp[]);
void		clean_and_exit(t_data *data, int status);
void		clean_child_ressources(t_data *data, int prev_pipe);
void		open_files(t_data *data, char *av[], int ac);
void		put_error(char *msg, char *cmd);
void		free_arr(char **arr);
void		close_fd(int fd);
pid_t		process_cmds(t_data *data, char *args[], int *prev_pipe, int i);
int			check_cmds_path(char *path, char *cmd);
int			get_exit_code(void);
int			ft_count_args(char *cmd);

#endif
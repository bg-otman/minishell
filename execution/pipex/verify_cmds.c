/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:35:56 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/21 18:09:44 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_cmd_path(char **cmd, char *path, int *exist_flag)
{
	char	*temp;

	if (ft_search(*cmd, '/'))
	{
		*exist_flag = 1;
		return ;
	}
	if (!(*exist_flag) && check_cmds_path(path, *cmd))
	{
		temp = ft_strdup(*cmd);
		free(*cmd);
		*cmd = ft_strjoin(path, temp);
		free(temp);
		*exist_flag = 1;
	}
}

static void	handle_single_quotes(char *cmd, char **cmd_arg, int *i, int *k)
{
	int	j;

	(*i)++;
	j = *i;
	while (cmd[*i] && cmd[*i] != '\'')
		(*i)++;
	if (cmd[*i] == '\'' || cmd[*i] == '\0')
		cmd_arg[(*k)++] = ft_substr(cmd, j, *i - j);
	if (cmd[*i] != '\0')
		(*i)++;
}

static void	handle_normal_word(char *cmd, char **cmd_arg, int *i, int *k)
{
	int	j;

	j = *i;
	while (cmd[*i] && cmd[*i] != ' ')
		(*i)++;
	if (*i > j)
		cmd_arg[(*k)++] = ft_substr(cmd, j, *i - j);
}

static char	**split_cmd(char *cmd)
{
	char	**cmd_arg;

	int (i), (k);
	i = 0;
	k = 0;
	cmd_arg = ft_calloc((ft_count_args(cmd) + 1), sizeof(char *));
	if (!cmd_arg)
		return (perror("Allocation fail"), NULL);
	while (cmd[i])
	{
		while (cmd[i] == ' ')
			i++;
		if (cmd[i] == '\'')
			handle_single_quotes(cmd, cmd_arg, &i, &k);
		else
			handle_normal_word(cmd, cmd_arg, &i, &k);
	}
	if (cmd_arg[0] == NULL)
	{
		free_arr(cmd_arg);
		cmd_arg = ft_split("/", ' ');
	}
	else
		cmd_arg[k] = NULL;
	return (cmd_arg);
}

void	verify_cmd(t_data *data, char *cmd)
{
	int	i;

	if (!ft_strcmp(cmd, ""))
		data->cmd = ft_split(".", ' ');
	else if (is_all_space(cmd))
		data->cmd = ft_split("\t", ' ');
	else
		data->cmd = split_cmd(cmd);
	if (!data->cmd)
	{
		perror("Allocation fail");
		clean_and_exit(data, EXIT_FAILURE);
	}
	i = 0;
	while (data->paths[i])
	{
		set_cmd_path(&data->cmd[0], data->paths[i], &data->exist_cmd);
		i++;
	}
}

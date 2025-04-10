/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_execs_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:55:10 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/21 09:40:12 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_slash(t_data *data)
{
	char	*temp;
	int		i;

	i = 0;
	while (data->paths[i])
	{
		temp = ft_strjoin(data->paths[i], "/");
		if (!temp)
			(perror("allocation fail"), clean_and_exit(data, EXIT_FAILURE));
		free(data->paths[i]);
		data->paths[i] = temp;
		i++;
	}
}

static void	get_path(t_data *data, char *env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			data->paths = ft_split(env[i] + 5, ':');
			if (!data->paths)
				(perror("allocation fail"), clean_and_exit(data, EXIT_FAILURE));
			break ;
		}
		i++;
	}
}

void	get_execs_paths(t_data *data, char *env[])
{
	if (!env[0])
	{
		data->paths = ft_split("/usr/bin/:/bin/:/usr/local/bin/", ':');
		if (!data->paths)
			(perror("allocation fail"), clean_and_exit(data, EXIT_FAILURE));
		return ;
	}
	get_path(data, env);
	if (!data->paths)
	{
		data->paths = ft_calloc(2, sizeof(char *));
		data->paths[0] = ft_strdup("");
		if (!data->paths || !data->paths[0])
			(perror("allocation fail"), clean_and_exit(data, EXIT_FAILURE));
		return ;
	}
	set_slash(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:03:35 by asajed            #+#    #+#             */
/*   Updated: 2025/04/19 10:06:20 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_expander	*expander(void)
{
	static t_expander	exp = {0};

	return (&exp);
}

void	add_env(void)
{
	t_expander	*shell;
	char		buff[4096];
	int			i;

	i = 0;
	shell = expander();
	while (shell->env && shell->env[i])
		shell->my_env = add_to_array(shell->my_env, shell->env[i++]);
	if (!shell->my_env || (!shell->my_env[0]))
	{
		shell->ignored = 1;
		shell->my_env = add_to_array(shell->my_env, ft_strjoin("PWD=",
					getcwd(buff, sizeof(buff))));
		shell->my_env = add_to_array(shell->my_env, "SHLVL=1");
		shell->my_env = add_to_array(shell->my_env, "_=/usr/bin/env");
		shell->my_env = add_to_array(shell->my_env,
				ft_strjoin("PATH=/usr/local/sbin:/usr/local/bin:",
					"/usr/sbin:/usr/bin:/sbin:/bin"));
	}
}

char	*odd_quotes(char *env_value)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (env_value && env_value[i])
		if (((env_value[i] == '\"' || env_value[i] == '\'')
				&& env_value[i++]) || env_value[i++])
			j++;
	new = ft_malloc(ft_strlen(env_value) + j);
	j = 0;
	i = 0;
	while (env_value && env_value[i])
	{
		if (env_value[i] == '\"' || env_value[i] == '\'')
			new[j++] = '\\';
		new[j++] = env_value[i++];
	}
	new[j] = 0;
	return (new);
}

char	*expand_line(char *line)
{
	char	*env_value;
	char	*start;
	char	*end;
	char	*tmp;

	line[ft_strlen(line) - 1] = 0;
	while (ft_strchr(line, '$') && get_var(line, 1))
	{
		start = get_start(line);
		end = get_end(line);
		tmp = get_var(line, 1);
		env_value = get_env(tmp);
		tmp = ft_strjoin(start, env_value);
		line = ft_strjoin(tmp, end);
	}
	return (line);
}

char	*call_heredoc(t_redir *redir)
{
	char	*file;
	int		fd;
	int		fd1;
	char	*tmp;

	if (!redir->expand)
		return (handle_heredoc(redir->file_name));
	redir->file_name = handle_heredoc(redir->file_name);
	file = ft_strdup(generate_tmp_name());
	fd = open(redir->file_name, redir->open_mode, 0666);
	fd1 = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1 || fd1 == -1)
		clean_and_exit("open here_doc ");
	tmp = get_next_line(fd);
	while (tmp)
	{
		if (ft_strchr(tmp, '$') && get_var(tmp, 1))
			tmp = ft_strjoin(expand_line(tmp), "\n");
		write(fd1, tmp, ft_strlen(tmp));
		tmp = get_next_line(fd);
	}
	close(fd);
	unlink(redir->file_name);
	close(fd1);
	return (file);
}

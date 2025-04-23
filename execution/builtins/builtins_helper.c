/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:50:16 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/17 17:10:08 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*remove_last_dir(char *path)
{
	int		i;
	char	*res;

	i = ft_strlen(path);
	while (i > 0 && path[i] != '/')
		i--;
	if (i == 0)
		return (ft_strdup("/"));
	res = ft_substr(path, 0, i);
	return (res);
}

void	update_old_pwd(char	*old_path)
{
	char	**env;
	int		i;

	i = 0;
	env = expander()->my_env;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 4))
		{
			env[i] = ft_strjoin("OLDPWD=", old_path);
			return ;
		}
		i++;
	}
}

int	count_args(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

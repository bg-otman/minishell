/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:00:15 by asajed            #+#    #+#             */
/*   Updated: 2025/05/03 10:40:01 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	add_default(char **new, t_token *old, t_data *data)
{
	int		i;
	t_token	*previous;
	t_token	*tmp;

	i = 0;
	previous = NULL;
	tmp = *(data->tokens);
	while (new[i])
		i++;
	while (tmp)
	{
		if (tmp == old)
		{
			if (previous && is_redirection(previous->value)
				&& ft_strcmp(previous->value, "<<") && i > 1)
			{
				tmp->value = NULL;
				return (1);
			}
		}
		previous = tmp;
		tmp = tmp->next;
	}
	add_words(new, old, data);
	return (0);
}

int	match_pattern(const char *pattern, const char *str, int i, char quote)
{
	if (*pattern == '\0' && *str == '\0')
		return (TRUE);
	if ((*pattern == '\'' || *pattern == '\"')
		&& (!quote || *pattern == quote))
		return (match_pattern(pattern + 1, str, (i == 0), *pattern));
	if (*pattern == '*' && !i)
		return (match_pattern(pattern + 1, str, i, quote) || (*str
				&& match_pattern(pattern, str + 1, i, quote)));
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1, i, quote));
	return (FALSE);
}

char	**compare_pattern(char *pattern)
{
	DIR				*dir;
	struct dirent	*files;
	char			**arr;
	char			*name;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	files = readdir(dir);
	arr = NULL;
	while (files)
	{
		name = ft_strdup(files->d_name);
		if (pattern[ft_strlen(pattern) - 1] == '/' && files->d_type == 4)
			name = ft_strjoin(files->d_name, "/");
		if (pattern[0] != '.' && files->d_name[0] == '.')
			;
		else if (match_pattern(pattern, name, 0, 0))
			arr = add_to_array(arr, odd_quotes(name));
		files = readdir(dir);
	}
	closedir(dir);
	return (arr);
}

void	expand_wildcard(t_data *data)
{
	t_token	*tmp;
	t_token	*next;
	char	**arr;

	if (!data->tokens)
		return ;
	tmp = *(data->tokens);
	while (tmp)
	{
		if (tmp->value && ft_strchr(tmp->value, '*'))
		{
			next = tmp->next;
			arr = compare_pattern(tmp->value);
			if (arr)
				add_default(arr, tmp, data);
			tmp = next;
			continue ;
		}
		tmp = tmp->next;
	}
	return ;
}

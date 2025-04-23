/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:00:15 by asajed            #+#    #+#             */
/*   Updated: 2025/04/23 15:28:39 by asajed           ###   ########.fr       */
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
			if (previous && is_redirection(previous->value) && i > 1)
			{
				data->error = 1;
				fdprintf(2, "minishell: %s: ambiguous redirect\n", old->value);
				return (1);
			}
		}
		previous = tmp;
		tmp = tmp->next;
	}
	add_words(new, old, data);
	return (0);
}

int	match_midlle(char **segs, char *file)
{
	int		i;
	char	*found;

	i = 1;
	if (!segs || !segs[0] || !segs[1])
		return (1);
	while (segs && segs[i + 1])
	{
		found = ft_strnstr(file, segs[i], ft_strlen(file));
		if (!found)
			return (0);
		file = found + ft_strlen(segs[i++]);
	}
	return (1);
}

int	match(char *pattern, char *file)
{
	int		i;
	int		j;
	int		start_j;
	char	**segs;

	i = 0;
	j = 0;
	if (!ft_strncmp(".", file, 1) && pattern[0] != '.')
		return (0);
	while (file[j] && pattern[i] && pattern[i] != '*')
		if (pattern[i++] != file[j++])
			return (0);
	start_j = j;
	i = ft_strlen(pattern) - 1;
	j = ft_strlen(file) - 1;
	if (!j && i && pattern[i] != '*')
		return (0);
	while (i > 0 && j > 0 && pattern[i] != '*')
		if (pattern[i--] != file[j--])
			return (0);
	segs = ft_split(pattern, '*');
	return (match_midlle(segs, ft_substr(file, start_j, j - start_j + 1)));
}

int	match_pattern(const char *pattern, const char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (true);
	if (*pattern == '*')
		return (match_pattern(pattern + 1, str) || (*str
				&& match_pattern(pattern, str + 1)));
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	return (false);
}

char	**compare_pattern(char *pattern)
{
	DIR				*dir;
	struct dirent	*files;
	char			**arr;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	files = readdir(dir);
	arr = ft_split("     ", ' ');
	while (files)
	{
		if (match_pattern(pattern, files->d_name))
			arr = add_to_array(arr, files->d_name);
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
		if (tmp->value && ft_strchr(tmp->value, '*') && tmp->state == DEFAULT)
		{
			next = tmp->next;
			arr = compare_pattern(tmp->value);
			if (arr[0])
				add_default(arr, tmp, data);
			tmp = next;
			continue ;
		}
		tmp = tmp->next;
	}
	return ;
}

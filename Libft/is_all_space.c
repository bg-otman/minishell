/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_all_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:53:50 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/12 15:13:30 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	is_all_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && ft_whitespace(cmd[i]))
		i++;
	if (cmd[i] == '\0')
		return (1);
	else
		return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:05:32 by obouizi           #+#    #+#             */
/*   Updated: 2025/02/21 18:07:30 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_search(char *haystack, char needle)
{
	int	i;

	if (!haystack)
		return (0);
	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle)
			return (1);
		i++;
	}
	return (0);
}

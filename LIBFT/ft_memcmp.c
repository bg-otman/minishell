/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:35:33 by asajed            #+#    #+#             */
/*   Updated: 2024/10/24 17:55:05 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*to_s1;
	unsigned char	*to_s2;
	size_t			i;

	to_s1 = (unsigned char *)s1;
	to_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (to_s1[i] != to_s2[i])
		{
			return (to_s1[i] - to_s2[i]);
		}
		i++;
	}
	return (0);
}

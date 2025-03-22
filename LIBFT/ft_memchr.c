/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:42:53 by asajed            #+#    #+#             */
/*   Updated: 2024/10/24 14:28:33 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*v;

	i = 0;
	v = (unsigned char *)s;
	while (i < n)
	{
		if (v[i] == (unsigned char)c)
			return (v + i);
		i++;
	}
	return (NULL);
}

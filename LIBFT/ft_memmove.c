/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:54:36 by asajed            #+#    #+#             */
/*   Updated: 2024/10/24 12:02:09 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*to_dst;
	const unsigned char	*to_src;

	to_dst = (unsigned char *)dst;
	to_src = (unsigned char *)src;
	i = 0;
	if (to_dst == to_src || len == 0)
		return (dst);
	if (to_dst < to_src)
	{
		while (i < len)
		{
			to_dst[i] = to_src[i];
			i++;
		}
	}
	else if (to_dst > to_src)
	{
		while (len-- > 0)
		{
			to_dst[len] = to_src[len];
		}
	}
	return (dst);
}

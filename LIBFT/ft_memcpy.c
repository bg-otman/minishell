/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:51:09 by asajed            #+#    #+#             */
/*   Updated: 2024/11/02 12:09:27 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*to_dst;
	const unsigned char	*to_src;

	to_dst = (unsigned char *)dst;
	to_src = (const unsigned char *)src;
	if (to_dst == to_src || !n)
		return (dst);
	i = 0;
	if (to_dst == to_src || !n)
		return (dst);
	while (i < n)
	{
		to_dst[i] = to_src[i];
		i++;
	}
	return (dst);
}

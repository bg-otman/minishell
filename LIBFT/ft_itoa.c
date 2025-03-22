/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:52:50 by asajed            #+#    #+#             */
/*   Updated: 2024/10/28 17:48:03 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count_n(int n)
{
	int	j;

	j = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		j++;
	while (n != 0)
	{
		n = n / 10;
		j++;
	}
	return (j);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		j;
	long	nb;

	j = 0;
	nb = n;
	j = count_n(nb);
	if (nb < 0)
		nb = -nb;
	str = (char *)malloc(j + 1);
	if (!str)
		return (NULL);
	str[j] = '\0';
	j--;
	while (j >= 0)
	{
		str[j] = nb % 10 + '0';
		nb = nb / 10;
		j--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

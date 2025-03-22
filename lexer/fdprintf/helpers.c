/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:14:08 by asajed            #+#    #+#             */
/*   Updated: 2025/03/21 02:07:09 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdprintf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_unsign_fd(unsigned int n, int fd)
{
	int		result;
	char	c;

	result = 0;
	if (n >= 10)
		result += ft_unsign_fd(n / 10, fd);
	c = n % 10 + '0';
	result += ft_putchar_fd(c, fd);
	return (result);
}

int	ft_address_fd(unsigned long long n, char *base, int fd)
{
	int		result;
	char	c;

	result = 0;
	if (n >= 16)
		result += ft_address_fd(n / 16, base, fd);
	c = base[n % 16];
	result += ft_putchar_fd(c, fd);
	return (result);
}

int	ft_putnbr_base_fd(unsigned int n, char *base, int fd)
{
	int		len;
	int		i;
	char	str[100];

	len = 0;
	i = 0;
	while (base[len])
		len++;
	if (n == 0)
		return (ft_putchar_fd('0', fd));
	while (n)
	{
		str[i++] = base[n % len];
		n /= len;
	}
	while (i--)
		ft_putchar_fd(str[i], fd);
	return (i);
}

int	ft_putnbr_fd(int n, int fd)
{
	int		result;
	char	c;

	result = 0;
	if (n < 0)
	{
		result += ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
		result += ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	result += ft_putchar_fd(c, fd);
	return (result);
}

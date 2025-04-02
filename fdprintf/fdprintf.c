/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:14:05 by asajed            #+#    #+#             */
/*   Updated: 2025/03/21 02:03:30 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdprintf.h"

int	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return (ft_putstr_fd("(null)", fd));
	return (write(fd, s, ft_strlen(s)));
}

int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_check(char c, va_list lst, int fd)
{
	if (c == 's')
		return (ft_putstr_fd(va_arg(lst, char *), fd));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(lst, int), fd));
	else if (c == 'x')
		return (ft_address_fd(va_arg(lst, unsigned int),
				"0123456789abcdef", fd));
	else if (c == 'X')
		return (ft_address_fd(va_arg(lst, unsigned int),
				"0123456789ABCDEF", fd));
	else if (c == 'c')
		return (ft_putchar_fd(va_arg(lst, int), fd));
	else if (c == 'u')
		return (ft_unsign_fd(va_arg(lst, unsigned int), fd));
	else if (c == 'p')
		return (ft_putstr_fd("0x", fd) + ft_address_fd(va_arg(lst,
					unsigned long long), "0123456789abcdef", fd));
	else if (c == '%')
		return (ft_putchar_fd('%', fd));
	else
		return (-1);
}

int	fdprintf(int fd, const char *str, ...)
{
	va_list	lst;
	int		result;
	int		j;
	int		i;

	result = 0;
	i = 0;
	va_start(lst, str);
	if (!str || fd < 0)
		return (va_end(lst), -1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			j = ft_check(str[++i], lst, fd);
			if (j < 0)
				return (va_end(lst), -1);
			result += j;
		}
		else
			result += ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(lst);
	return (result);
}

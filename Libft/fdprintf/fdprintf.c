/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:14:05 by asajed            #+#    #+#             */
/*   Updated: 2025/04/25 11:00:57 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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

	int (result), (j), (i), (start);
	result = 0;
	i = 0;
	start = 0;
	va_start(lst, str);
	while (str && str[i])
	{
		if (str[i] == '%')
		{
			if (start < i && write(fd, str + start, i - start))
				result += i - start;
			j = ft_check(str[++i], lst, fd);
			result += j;
			start = i + 1;
		}
		else if (i == 0 || str[i - 1] == '%')
			start = i;
		i++;
	}
	if (start < i && write(fd, str + start, i - start))
		result += i - start;
	va_end(lst);
	return (result);
}

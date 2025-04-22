/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:16:30 by asajed            #+#    #+#             */
/*   Updated: 2025/04/02 14:34:57 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDPRINTF_H
# define FDPRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_putnbr_base_fd(unsigned int n, char *base, int fd);
int		ft_address_fd(unsigned long long n, char *base, int fd);
int		ft_unsign_fd(unsigned int n, int fd);
size_t	ft_strlen(const char *s);

#endif // FDPRINTF_H
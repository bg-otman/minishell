/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:49:20 by obouizi           #+#    #+#             */
/*   Updated: 2025/04/01 13:51:37 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    put_error(const char *error_msg)
{
    write(2, error_msg, ft_strlen(error_msg));
    free_garbage();
    exit(1);
}

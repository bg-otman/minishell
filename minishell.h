/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:48:13 by asajed            #+#    #+#             */
/*   Updated: 2025/03/01 18:49:33 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_garbage
{
	void	*ptr;
	struct s_garbage *next;
}		t_garbage;


void garbage_collector(void);

typedef struct s_flags
{
	int		flag;
}		t_flags;

typedef struct s_tree
{
	char	*str;
	struct s_tree	*left;
	struct s_tree	*right;
}		t_tree;

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:03:06 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/01 22:12:17 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include "op.h"
# include "libft.h"
# include "ft_dprintf.h"

typedef struct	s_option
{
	bool	option;
	int		n;
}				t_option;

typedef struct	s_prog
{
	char		*path;
	t_option	dump;
	t_option	n;
}				t_prog;

void			assembler(char **input);
void			get_options(t_prog *info, char **input);
//
void			destroy_struct(t_prog *info);
void			terminate(t_prog *info, int status);
void			print_error(t_prog *info, int status);

#endif

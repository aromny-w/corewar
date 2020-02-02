/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:03:06 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/02 22:51:47 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# include "op.h"

typedef struct	s_asm
{
	char		*path;
	bool		flag;
	int			fd;
	char		*line;
	size_t		index;
	size_t		lines;
	t_header	header;
	bool		name;
	bool		comment;
}				t_asm;

void			assembler(char **input);
void			init_struct(t_asm *info, char **input);
void			read_file(t_asm *info);
void			parse_name(t_asm *info);
void			parse_comment(t_asm *info);
void			parse_instruction(t_asm *info);
void			terminate(int status, t_asm *info);

void			corewar(char *input);

#endif

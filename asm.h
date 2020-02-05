/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:03:06 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/05 19:25:46 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# include "op.h"

typedef struct	s_cmd
{
	char	*label;
	char	opcode;
	char	type[MAX_ARGS_NUMBER];
	char	*value[MAX_ARGS_NUMBER];
	char	size;
}				t_cmd;

typedef struct	s_asm
{
	char		*path;
	bool		flag;
	int			fd;
	char		*line;
	size_t		index;
	size_t		lines;
	t_header	header;
	t_cmd		*ops;
	size_t		n;
}				t_asm;

void			assembler(char **input);
void			init_struct(t_asm *info, char **input);
void			destroy_struct(t_asm *info);
void			read_file(t_asm *info);
void			parse_name(t_asm *info);
void			parse_comment(t_asm *info);
void			parse_operation(t_asm *info);
void			parse_arguments(t_asm *info);
void			skip_space(t_asm *info);
void			terminate(int status, t_asm *info);
void			print_status(t_asm *info); // debug

void			corewar(char *input);

#endif

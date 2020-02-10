/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:03:06 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/10 17:37:13 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# include "op.h"

typedef union	u_byte
{
	int				nbr;
	unsigned char	byte[4];
}				t_byte;

typedef struct	s_cmd
{
	char			*label;
	char			*name;
	unsigned char	opcode;
	unsigned char	opsize;
	char			type[MAX_ARGS_NUMBER];
	unsigned char	typecode;
	char			*arg[MAX_ARGS_NUMBER];
	unsigned char	*argcode[MAX_ARGS_NUMBER];
	unsigned char	argsize[MAX_ARGS_NUMBER];
	short			pos;
	struct s_cmd	*next;
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
	t_cmd		*op;
}				t_asm;

void			assembler(char **input);
void			init_struct(t_asm *info, char **input);
void			destroy_struct(t_asm *info);
void			read_file(t_asm *info);
void			parse_name(t_asm *info);
void			parse_comment(t_asm *info);
void			parse_operation(t_asm *info);
void			parse_opcode(t_asm *info);
void			parse_arguments(t_asm *info);
void			parse_argcode(t_asm *info);
void			set_size(t_asm *info);
void			write_file(t_asm *info);
void			skip_space(t_asm *info);
void			terminate(int status, t_asm *info);
void			print_status(t_asm *info); // debug

void			corewar(char *input);

#endif

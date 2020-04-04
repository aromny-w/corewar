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

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <stdio.h>
# include "op.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_dprintf.h"

typedef union	u_value
{
	int				nbr;
	unsigned char	byte[4];
}				t_value;

extern char	*g_type[];

typedef enum
{
	COMMAND,
	STRING,
	LABEL,
	INSTRUCTION,
	REGISTER,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	SEPARATOR,
	ENDLINE,
	END
}				t_type;

typedef struct	s_token
{
	char	*content;
	size_t	row;
	size_t	col;
	t_type	type;
}				t_token;

typedef struct	s_inst
{
	char			*label;
	char			*op;
	unsigned char	opcode;
	unsigned char	type[MAX_ARGS_NUMBER];
	unsigned char	typecode;
	int				arg[MAX_ARGS_NUMBER];
	unsigned char	argcode[MAX_ARGS_NUMBER];
	unsigned char	size;
	unsigned short	pos;
	struct s_inst	*next;
}				t_inst;

typedef struct	s_asm
{
	char		*path;
	char		*filename;
	bool		flag;
	char		**data;
	t_token		*token;
	size_t		tokens;
	t_header	header;
	bool		name_mark;
	bool		comment_mark;
	t_inst		*inst;
}				t_asm;

void			assembler(char **input);
void			init_struct(t_asm *info, char **input);
void			read_file(t_asm *info);
void			tokenize_data(t_asm *info);
void			lexical_check(t_asm *info, t_token token);
void			syntax_check(t_asm *info);
void			destroy_struct(t_asm *info);
void			terminate(t_asm *info, int status, t_token *token);

void			debug(t_asm *info);

#endif

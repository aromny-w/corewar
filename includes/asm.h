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
# include <errno.h>

typedef union	u_int
{
	int				n;
	unsigned char	byte[4];
}				t_int;

extern char	*g_type[];

typedef enum
{
	COMMAND_NAME,
	COMMAND_COMMENT,
	STRING,
	LABEL,
	INSTRUCTION,
	REGISTER,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	ENDLINE,
	SEPARATOR,
	END,
	COMMENT,
	WHITESPACE
}				t_type;

typedef struct	s_token
{
	char			*content;
	size_t			row;
	size_t			col;
	t_type			type;
	struct s_token	*next;
}				t_token;

typedef struct	s_arg
{
	t_token			*token;
	int				value;
	t_arg_type		type;
	unsigned int	size;
}				t_arg;

typedef struct	s_instr
{
	char			*label;
	t_op			op;
	t_arg			arg[MAX_ARGS_NUMBER];
	unsigned int	size;
	unsigned int	pos;
	struct s_instr	*next;
}				t_instr;

typedef struct	s_asm
{
	char		*path;
	char		*filename;
	bool		flag;
	char		*buf;
	char		**data;
	t_token		*token;
	t_header	header;
	t_instr		*instr;
}				t_asm;

void			assembler(char **input);
void			init_struct(t_asm *info, char **input);
void			read_file(t_asm *info);
void			tokenize_data(t_asm *info);
void			lexical_check(t_asm *info);
void			syntax_check(t_asm *info);
void			parse_tokens(t_asm *info);
void			dereference_tokens(t_asm *info);
void			write_to_file(t_asm *info);
void			destroy_struct(t_asm *info);
void			terminate(t_asm *info, int status, t_token *token);

void			debug(t_asm *info);

#endif

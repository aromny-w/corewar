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
# include <errno.h>
# include "op.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_dprintf.h"

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
	char	*content;
	t_type	type;
	int		row;
	int		col;
	struct s_token	*next;
}				t_token;

typedef struct	s_arg
{
	t_token		*token;
	int			value;
	t_arg_type	type;
	int			size;
}				t_arg;

typedef struct	s_instr
{
	char			*label;
	t_op			op;
	t_arg			arg[MAX_ARGS_NUMBER];
	int				acb;
	int				size;
	int				pos;
	struct s_instr	*next;
}				t_instr;

typedef struct	s_line
{
	t_token 		*label;
	t_instr			*instr;
	int				size;
	int				pos;
	struct s_line	*next;
}				t_line;

typedef struct	s_flag
{
	bool	a;
	bool	s;
	int		n;
}				t_flag;

typedef struct	s_prog
{
	char		*path;
	char		*filename;
	t_flag		flag;
	char		*buf;
	char		**data;
	t_token		*token;
	t_header	header;
	t_instr		*instr;
}				t_prog;

void			assembler(char **input);
void			init_struct(t_prog *info, char **input);
void			read_file(t_prog *info);
void			tokenize_data(t_prog *info);
void			reverse_tokens(t_token **token);
void			lexical_check(t_prog *info);
void			syntax_check(t_prog *info);
void			parse_tokens(t_prog *info);
void			reverse_instr(t_instr **instr);
void			dereference_tokens(t_prog *info);
void			write_bytecode(t_prog *info);
void			print_annotation(t_prog *info);
void			destroy_struct(t_prog *info);
void			terminate(t_prog *info, int status, t_token *token);

unsigned int	get_label_pos(t_prog *info, t_token *token);

void			debug(t_prog *info, bool data, bool token, bool instr);

#endif

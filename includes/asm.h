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
}	t_type;

typedef struct	s_token
{
	char			*str;
	t_type			type;
	int				row;
	int				col;
	struct s_token	*next;
}				t_token;

typedef struct	s_arg
{
	t_token		*token;
	char		*ref;
	int			value;
	t_arg_type	type;
	int			size;
}				t_arg;

typedef struct	s_line
{
	t_token			*label;
	t_op			op;
	t_arg			arg[MAX_ARGS_NUMBER];
	int				acb;
	int				size;
	int				pos;
	struct s_line	*next;
}				t_line;

typedef struct	s_prog
{
	char		*path;
	char		*filename;
	bool		option;
	char		*buf;
	char		**data;
	t_token		*token;
	t_header	header;
	t_line		*line;
}				t_prog;

void			assembler(char **input);
void			get_options(t_prog *info, char **input);
void			get_file_contents(t_prog *info);
void			lex_corewar(t_prog *info);
char			*get_token_str(char *s);
t_type			get_token_type(char *content);
void			lexical_check(t_prog *info, char *s);
void			syntax_check(t_prog *info);
void			strip_tokens(t_prog *info);
void			parse_tokens(t_prog *info);
void			parse_lines(t_prog *info);
void			dereference_labels(t_prog *info);
void			bytecode_output(t_prog *info);
void			annotated_output(t_prog *info);
void			destroy_struct(t_prog *info);
void			terminate(t_prog *info, int status, void *ptr);
void			print_error(t_prog *info, int status, void *ptr);

#endif

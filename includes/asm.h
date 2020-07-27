/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.21-school.ru>   +#+  +:+       +#+        */
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
# include "libft.h"
# include "op.h"

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

typedef struct	s_tok
{
	char			*content;
	t_type			type;
	int				row;
	int				col;
	struct s_tok	*next;
}				t_tok;

typedef struct	s_arg
{
	t_tok		*token;
	char		*ref;
	int			value;
	t_arg_type	type;
	int			size;
}				t_arg;

typedef struct	s_line
{
	t_tok			*label;
	t_op			op;
	t_arg			arg[MAX_ARGS_NUMBER];
	int				acb;
	int				size;
	int				pos;
	struct s_line	*next;
}				t_line;

typedef struct	s_exec
{
	char		*path;
	char		*filename;
	bool		option;
	char		*buf;
	t_tok		*token;
	t_header	header;
	t_line		*line;
}				t_exec;

void			assembler(char **input);
void			get_options(t_exec *info, char **input);
void			get_file_contents(t_exec *info);
void			lex_corewar(t_exec *info);
char			*get_token_content(char *s);
t_type			get_token_type(char *s);
void			lexical_check(t_exec *info, char *s);
void			syntax_check(t_exec *info);
void			strip_tokens(t_exec *info);
void			parse_tokens(t_exec *info);
void			parse_lines(t_exec *info);
void			dereference_labels(t_exec *info);
void			bytecode_output(t_exec *info);
void			annotated_output(t_exec *info);
void			destroy_struct(t_exec *info);
void			terminate(t_exec *info, int status, void *ptr);
void			print_error(t_exec *info, int status, void *ptr);

#endif

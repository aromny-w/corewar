/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:05:05 by malannys          #+#    #+#             */
/*   Updated: 2020/08/03 18:05:10 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASM_H
# define DISASM_H

# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>

# include "op.h"
# include "libft.h"

# define RESET_COLOR "\e[m"
# define RED "\033[4;31m"

typedef struct		s_instruction
{
	t_op					op;
	t_arg_type				arg_type[MAX_ARGS_NUMBER];
	int32_t					arg_val[MAX_ARGS_NUMBER];
	struct s_instruction	*next;
}					t_instruction;

typedef struct		s_bin
{
	char					*filename;
	char					*prog_name;
	size_t					prog_size;
	char					*comment;
	uint8_t					*code;
	struct s_instruction	*instr;
}					t_bin;

t_bin				*init_bin(void);
t_instruction		*init_instruction(void);
void				push_back(t_instruction **head, t_instruction *new);

void				parse_bin(t_bin *bin, char *av);

int32_t				bin_to_num(uint8_t *val, size_t len);
int					rows_count(char **arr);

void				disassemble(t_bin *bin);

void				write_asm(t_bin *bin);

void				free_bin(t_bin **bin);
void				free_instruction(t_instruction **instr);

void				error(char *str);

#endif

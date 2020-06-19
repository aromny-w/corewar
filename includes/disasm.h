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
//# include "ft_dprintf.h"

# define RESET_COLOR "\e[m"
# define RED "\033[4;31m"

typedef struct      s_instruction
{
	t_op					op;
	char					*name; //hm?
	t_arg_type				arg_type[MAX_ARGS_NUMBER];
	int32_t					arg_val[MAX_ARGS_NUMBER];
	struct s_instruction	*next;
}					t_instruction;

typedef struct		s_bin
{
	char            		*filename;
	char					*prog_name;
	size_t       			prog_size;
	char					*comment;
	uint8_t					*code;
	struct s_instruction	*instr;
}					t_bin;

t_bin	*init_bin(void);

void	parse_bin(t_bin *bin, char *av);

int32_t bin_to_num(uint8_t *val, size_t len);

void	disassemble(t_bin *bin);

void	write_asm(t_bin *bin);

void	free_bin(t_bin **bin);
void	free_instruction(t_instruction **instr);

void	error(char *str);

#endif
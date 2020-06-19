#include "disasm.h"

void	free_instruction(t_instruction **instr)
{
    if (!instr || !*instr)
		return ;
	if ((*instr)->next)
		free_instruction(&(*instr)->next);
	free((*instr)->name);
	ft_bzero(*instr, sizeof(t_instruction));
	free(*instr);
	*instr = NULL;
}

void    free_bin(t_bin **bin)
{
	if (!bin || !*bin)
		return ;
	free_instruction(&(*bin)->instr);
	free((*bin)->filename);
	free((*bin)->prog_name);
	free((*bin)->comment);
	free((*bin)->code);
	ft_bzero(*bin, sizeof(t_bin));
	free(*bin);
	*bin = NULL;
}
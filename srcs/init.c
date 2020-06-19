#include "disasm.h"

t_bin   *init_bin(void)
{
    t_bin   *bin;

    if (!(bin = (t_bin *)ft_memalloc(sizeof(t_bin))))
        error("Malloc failure.");
    return (bin);
}

t_instruction   *init_instruction(void)
{
    t_instruction   *instr;

    if (!(instr = \
            (t_instruction *)ft_memalloc(sizeof(t_instruction))))
        error("Malloc failure.");
    return (instr);
}
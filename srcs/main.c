#include "disasm.h"

int	main(int ac, char **av)
{
	t_bin	*bin;
	int		i;

	i = 0;
	while (++i < ac)
	{
		bin = init_bin();
		parse_bin(bin, av[i]);
		disassemble(bin);
		write_asm(bin);
		free_bin(&bin);
		bin = NULL;
	}
	return 0;
}

#include "vm.h"

int32_t bin_to_num(uint8_t *val, size_t len)
{
	int32_t	sign;
	int32_t	res;
	size_t	i;
	uint8_t	*tmp;

	i = 0;
	res = 0;
	if (!(tmp = (uint8_t *)ft_memalloc(sizeof(uint8_t) * len)))
		error("Malloc failure.");
	tmp = ft_memcpy(tmp, val, len);
	sign = tmp[0] & 0x80 ? 1 : 0;
	while (i < len)
	{
		if (sign)
			tmp[len - i - 1] = ~tmp[len - i - 1];
		res += tmp[len - i - 1] << (8 * i);
		i++;
	}
	res += sign;
	free(tmp);
	return (sign ? -res : res);
}

void		print_usage(char *exec)
{
	ft_putstr_fd(exec, 2);
	ft_putstr_fd(" Imagine printed usage here.\n", 1);
	/*ft_printf("Usage: %s [-dump N] [-n N] <champion1.cor> <...>\n", exec);
	ft_printf("    -dump N   : Dumps memory after N cycles then exits\n");
	ft_printf("    -n N      : Sets N number of the next player\n");*/
	exit(1);
}
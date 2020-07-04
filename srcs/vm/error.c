#include "vm.h"

void	error(char *str)
{
    /*
    ft_dprintf(2, "%s\nERROR: ", RED);
    if (errno)
		ft_dprintf(2, "%s ", strerror(errno));
    ft_dprintf(2, "%s%s\n", str, RESET_COLOR);
    */
    ft_putstr_fd(RED, 2);
    ft_putstr_fd("\nERROR: ", 2);
    if (errno)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, " ", 1);
	}
    ft_putstr_fd(str, 2);
    ft_putstr_fd(RESET_COLOR, 2);
    write(2, "\n", 1);
    exit(1);
}
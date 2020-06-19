#include "disasm.h"

void	error(char *str)
{
    char	*errorbuff;

    /*
    ft_dprintf(2, "%s\nERROR: ", RED);
    if ((errorbuff = strerror(errno)))
		  ft_dprintf(2, "%s ", errorbuff);
    ft_dprintf(2, "%s%s\n", str, RESET_COLOR);
    */
    ft_putstr_fd(RED, 2);
    ft_putstr_fd("\nERROR: ", 2);
    if ((errorbuff = strerror(errno)))
		  ft_putstr_fd(errorbuff, 2);
    write(2, " ", 1);
    ft_putstr_fd(str, 2);
    ft_putstr_fd(RESET_COLOR, 2);
    write(2, "\n", 1);
    exit(1);
}
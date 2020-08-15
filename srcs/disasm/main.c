/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:05:05 by malannys          #+#    #+#             */
/*   Updated: 2020/08/03 18:05:10 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"
#include "ft_printf.h"

int	main(int ac, char **av)
{
	t_bin	*bin;
	int		i;

	i = 0;
	if (ac < 2)
		ft_printf("usage: ./disasm <champion1.cor> [<champion2.cor> ...]\n");
	else
	{
		while (++i < ac)
		{
			bin = init_bin();
			parse_bin(bin, av[i]);
			disassemble(bin);
			write_asm(bin);
			free_bin(&bin);
			bin = NULL;
		}
	}
	return (0);
}

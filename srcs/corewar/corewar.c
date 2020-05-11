/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 16:57:41 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/21 03:09:26 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_usage(char *exec)
{
	ft_printf("Usage: %s [-dump N] [-n N] <champion1.cor> <...>\n", exec);
	ft_printf("    -dump N   : Dumps memory after N cycles then exits\n");
	ft_printf("    -n N      : Sets N number of the next player\n");
}

void		corewar(char **input)
{
	t_prog	info;

	get_options(&info, input);
	//
	destroy_struct(&info);
}

int			main(int argc, char **argv)
{
	if (argc > 1)
		corewar(argv);
	else
		print_usage(argv[0]);
	exit(EXIT_SUCCESS);
}

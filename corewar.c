/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 21:06:12 by aromny-w          #+#    #+#             */
/*   Updated: 2019/12/22 21:12:08 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	corewar(char *input)
{
	(void)input;
}

int		main(int argc, char **argv)
{
	if (argc == 2)
		corewar(argv[1]);
	else
		ft_printf("Usage: ./corewar <champion1.cor> <...>\n");
	return (0);
}

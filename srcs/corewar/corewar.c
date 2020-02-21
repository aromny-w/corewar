/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 21:06:12 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/21 16:38:50 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	corewar(char *input)
{
	(void)input;
}

int		main(int argc, char **argv)
{
	if (argc > 1)
		corewar(argv[1]);
	else
		ft_printf("Usage: ./corewar <champion1.cor> <...>\n");
	return (0);
}

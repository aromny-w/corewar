/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 16:57:41 by aromny-w          #+#    #+#             */
/*   Updated: 2020/03/13 17:34:40 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	assembler(char **input)
{
	(void)input;
}

int		main(int argc, char **argv)
{
	if (argc > 1)
		assembler(++argv);
	else
		ft_printf("Usage: ./asm [-a] <sourcefile.s>\n");
	exit(EXIT_SUCCESS);
}

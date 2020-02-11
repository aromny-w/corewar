/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 16:57:41 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/11 17:18:48 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	assembler(char **input)
{
	t_asm	info;

	init_struct(&info, input);
	read_file(&info);
	if (!info.flag)
		write_file(&info);
	//else
	//	write_stdout(&info);
	//print_status(&info); // debug
}

int		main(int argc, char **argv)
{
	if (argc > 1)
		assembler(argv);
	else
		ft_printf("Usage: ./asm [-a] <sourcefile.s>\n");
	exit(EXIT_SUCCESS);
}

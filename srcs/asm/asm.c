/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 16:57:41 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/21 03:09:26 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_usage(char *exec)
{
	ft_printf("Usage: %s [-a] <sourcefile.s>\n", exec);
	ft_printf("    -a : Instead of creating a .cor file, outputs a stripped and\
annotated version of the code to the standard output");
}

void		assembler(char **input)
{
	t_asm	info;

	init_struct(&info, input);
	read_file(&info);
	tokenize_data(&info);
	parse_tokens(&info);
	write_to_file(&info);
	//debug(&info);
	destroy_struct(&info);
}

int			main(int argc, char **argv)
{
	if (argc > 1)
		assembler(argv);
	else
		print_usage(argv[0]);
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:48:33 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/05 18:03:02 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_status(t_asm *info)
{
	size_t	i;

	i = -1;
	ft_printf("Name: %s\n", info->header.prog_name);
	ft_printf("Comment: %s\n", info->header.comment);
	ft_printf("%2c%8s %17d%24d%24d%24d\n",'#', "Label", 1, 2, 3, 4);
	while (++i < info->n)
		ft_printf("%3d: %-7s %-4s [%-21s] [%-21s] [%-21s] [%-21s]\n", i, info->ops[i].label, g_op_tab[info->ops[i].opcode - 1].name, info->ops[i].value[0], info->ops[i].value[1], info->ops[i].value[2], info->ops[i].value[3]);
}

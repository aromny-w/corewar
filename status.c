/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:48:33 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/11 15:50:26 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_status(t_asm *info)
{
	size_t	i;

	ft_printf("Name: %s\n", info->header.prog_name);
	ft_printf("Comment: %s\n", info->header.comment);
	ft_printf("%2c%12s%22d%24d%24d%24d\n", '#', "label", 1, 2, 3, 4);
	i = -1;
	while (info->op)
	{
		ft_printf("%3d: [%-11s] %-4s %d %3d [%-21s] [%-21s] [%-21s] [%-21s]\n", ++i,
		info->op->label ? info->op->label : "",
		info->op->opcode ? g_op_tab[info->op->opcode - 1].op : "",
		info->op->opsize,
		info->op->pos,
		info->op->arg[0] ? info->op->arg[0] : "",
		info->op->arg[1] ? info->op->arg[1] : "",
		info->op->arg[2] ? info->op->arg[2] : "",
		info->op->arg[3] ? info->op->arg[3] : "");
		info->op = info->op->next;
	}
	ft_printf("%d\n", info->header.prog_size);
}

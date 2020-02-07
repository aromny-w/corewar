/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:48:33 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/07 14:53:06 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_status(t_asm *info)
{
	size_t	i;
	size_t	size;

	ft_printf("Name: %s\n", info->header.prog_name);
	ft_printf("Comment: %s\n", info->header.comment);
	ft_printf("%2c%12s%22d%24d%24d%24d\n", '#', "label", 1, 2, 3, 4);
	size = 0;
	i = -1;
	while (info->op)
	{
		ft_printf("%3d: [%-11s] %-4s [%-21s] [%-21s] [%-21s] [%-21s]\n", ++i,
		info->op->label ? info->op->label : "",
		info->op->opcode ? g_op_tab[info->op->opcode - 1].name : "",
		info->op->value[0] ? info->op->value[0] : "",
		info->op->value[1] ? info->op->value[1] : "",
		info->op->value[2] ? info->op->value[2] : "",
		info->op->value[3] ? info->op->value[3] : "");
		size += info->op->size;
		info->op = info->op->next;
	}
	ft_printf("%d\n", size);
}

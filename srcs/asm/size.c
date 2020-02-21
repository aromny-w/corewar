/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 21:59:30 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 18:11:13 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	set_size(t_asm *info)
{
	int	i;

	info->op->opsize += 1;
	if (g_op_tab[info->op->opcode - 1].type[0] != 2)
		info->op->opsize += 1;
	i = -1;
	while (++i < g_op_tab[info->op->opcode - 1].args)
	{
		if (!(info->op->type[i] & g_op_tab[info->op->opcode - 1].type[i]))
			terminate(info, 0); // invalid argtype
		else if (info->op->type[i] == T_REG)
			info->op->opsize += (info->op->argsize[i] = 1);
		else if (info->op->type[i] == T_DIR &&
		g_op_tab[info->op->opcode - 1].dir_size)
			info->op->opsize += (info->op->argsize[i] = 2);
		else if (info->op->type[i] == T_DIR)
			info->op->opsize += (info->op->argsize[i] = 4);
		else if (info->op->type[i] == T_IND)
			info->op->opsize += (info->op->argsize[i] = 2);
	}
	info->header.prog_size += info->op->opsize;
}

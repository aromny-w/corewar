/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 21:59:30 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/07 14:49:46 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	set_size(t_asm *info)
{
	int		i;

	info->op->size += 1;
	if (g_op_tab[info->op->opcode - 1].type[0] != 2)
		info->op->size += 1;
	i = -1;
	while (++i < g_op_tab[info->op->opcode - 1].args)
	{
		if (!(info->op->type[i] & g_op_tab[info->op->opcode - 1].type[i]))
			terminate(0, info); // invalid argtype
		else if (info->op->type[i] == T_REG)
			info->op->size += 1;
		else if (info->op->type[i] == T_DIR &&
		g_op_tab[info->op->opcode - 1].dir_size)
			info->op->size += 2;
		else if (info->op->type[i] == T_DIR)
			info->op->size += 4;
		else if (info->op->type[i] == T_IND)
			info->op->size += 2;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 21:59:30 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/05 22:17:27 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	set_size(t_asm *info)
{
	int	i;

	info->ops[info->n - 1].size += 1;
	if ((g_op_tab[info->ops[info->n - 1].opcode - 1].type[0] | 1) != 1)
		info->ops[info->n - 1].size += 1;
	i = -1;
	while (++i < g_op_tab[info->ops[info->n - 1].opcode - 1].args)
	{
		if (!(info->ops[info->n - 1].type[i] &
		g_op_tab[info->ops[info->n - 1].opcode - 1].type[i]))
			terminate(0, info); // invalid argtype
		//else if (info->ops[info->n - 1].type[i] == T_REG)
	}
}

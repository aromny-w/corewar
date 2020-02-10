/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:30:41 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/10 13:33:43 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse_opcode(t_asm *info)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (ft_islower(info->line[info->index + i]))
		i++;
	j = 0;
	while (g_op_tab[j].op && ft_strncmp(&info->line[info->index],
	g_op_tab[j].op, i))
		j++;
	if (!g_op_tab[j].op)
		terminate(0, info);
	info->op->name = g_op_tab[j].op;
	info->op->opcode = g_op_tab[j].opcode;
	info->index += i;
	skip_space(info);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 12:52:14 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/04 22:36:36 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	parse_instruction(t_asm *info)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (ft_islower(info->line[info->index + i]))
		i++;
	j = 0;
	while (g_op_tab[j].name && ft_strncmp(&info->line[info->index],
	g_op_tab[j].name, i))
		j++;
	if (!g_op_tab[j].name)
		terminate(0, info);
	info->ops[info->n - 1].opcode = g_op_tab[j].opcode;
	info->index += i;
	skip_space(info);
}

void		parse_operation(t_asm *info)
{
	parse_label(info);
	parse_instruction(info);
	parse_arguments(info);
}

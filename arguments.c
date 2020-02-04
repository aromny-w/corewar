/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:18:55 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/04 22:37:24 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	parse_direct(t_asm *info, size_t n)
{
	(void)info;
	(void)n;
}

static void	parse_register(t_asm *info, size_t n)
{
	char	reg;
	size_t	i;

	info->ops[info->n - 1].type[n] = T_DIR;
	i = 0;
	if (!ft_isdigit(info->line[info->index + ++i]))
		terminate(0, info); // invalid instr
	reg = 0;
	while (ft_isdigit(info->line[info->index]) && reg >= 0 && reg <= 16)
		reg = 10 * reg + info->line[info->index + i++] - '0';
	if (!(reg > 0 && reg <= 16))
		terminate(0, info); // invalid instr
	info->ops[info->n - 1].value[n] = reg;
	skip_space(info);
}

void	parse_arguments(t_asm *info)
{
	size_t	i;

	i = 0;
	while (i < g_op_tab[info->ops[info->n - 1].opcode - 1].args)
	{
		if (!info->line[info->index])
			terminate(0, info); // endline
		else if (info->line[info->index] == 'r')
			parse_register(info, i);
		else if (info->line[info->index] == DIRECT_CHAR)
			parse_direct(info, i);
	}
	skip_space(info);
}

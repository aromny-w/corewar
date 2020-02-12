/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:18:55 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 17:11:25 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	parse_inderect(t_asm *info, size_t i)
{
	size_t	j;

	info->op->type[i] = T_IND;
	info->op->typecode += IND_CODE << (8 - (i + 1) * 2);
	j = 0;
	if (info->line[info->index + j] == '-' ||
		info->line[info->index + j] == '+')
		j++;
	if (ft_isdigit(info->line[info->index + j]))
		while (ft_isdigit(info->line[info->index + j]))
			j++;
	else if (info->line[info->index + j++] == LABEL_CHAR)
		while (info->line[info->index + j] &&
		ft_strchr(LABEL_CHARS, info->line[info->index + j]))
			j++;
	else
		terminate(0, info); // syntax error
	info->op->argbuf[i] = ft_strndup(&info->line[info->index], j);
	info->index += j;
	skip_space(info);
}

static void	parse_direct(t_asm *info, size_t i)
{
	size_t	j;

	info->op->type[i] = T_DIR;
	info->op->typecode += DIR_CODE << (8 - (i + 1) * 2);
	j = 1;
	if (info->line[info->index + j] == '-' ||
		info->line[info->index + j] == '+')
		j++;
	if (ft_isdigit(info->line[info->index + j]))
		while (ft_isdigit(info->line[info->index + j]))
			j++;
	else if (info->line[info->index + j++] == LABEL_CHAR)
		while (info->line[info->index + j] &&
		ft_strchr(LABEL_CHARS, info->line[info->index + j]))
			j++;
	else
		terminate(0, info); // syntax error
	info->op->argbuf[i] = ft_strndup(&info->line[info->index], j);
	info->index += j;
	skip_space(info);
}

static void	parse_register(t_asm *info, size_t i)
{
	unsigned short	reg;
	size_t			j;

	info->op->type[i] = T_REG;
	info->op->typecode += REG_CODE << (8 - (i + 1) * 2);
	j = 1;
	if (!ft_isdigit(info->line[info->index + j]))
		terminate(0, info); // invalid instr
	reg = 0;
	while (ft_isdigit(info->line[info->index + j]) && reg <= REG_NUMBER)
		reg = 10 * reg + info->line[info->index + j++] - '0';
	if (!(reg >= 1 && reg <= REG_NUMBER))
		terminate(0, info); // invalid instr
	info->op->argbuf[i] = ft_strndup(&info->line[info->index], j);
	info->index += j;
	skip_space(info);
}

void		parse_arguments(t_asm *info)
{
	char	i;

	i = -1;
	while (++i < g_op_tab[info->op->opcode - 1].args)
	{
		if (!info->line[info->index])
			terminate(0, info); // endline
		else if (info->line[info->index] == 'r')
			parse_register(info, i);
		else if (info->line[info->index] == DIRECT_CHAR)
			parse_direct(info, i);
		else if (ft_isdigit(info->line[info->index]) ||
		info->line[info->index] == '-' || info->line[info->index] == '+' ||
		info->line[info->index] == LABEL_CHAR)
			parse_inderect(info, i);
		else
			terminate(0, info); // invalid instr
		if (i + 1 < g_op_tab[info->op->opcode - 1].args &&
		info->line[info->index++] != SEPARATOR_CHAR)
			terminate(0, info); // invalid instr
		skip_space(info);
	}
	if (info->line[info->index] && info->line[info->index] != COMMENT_CHAR &&
	info->line[info->index] != COMMENT_CHAR_2)
		terminate(0, info); // invalid instr
}

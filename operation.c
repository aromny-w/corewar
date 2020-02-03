/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 12:52:14 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/03 19:31:01 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	parse_arguments(t_asm *info)
{
	size_t	i;

	if (!info->line[info->index])
		terminate(0, info); // endline
	i = 0;
	skip_space(info);
}

static void	parse_instruction(t_asm *info)
{
	size_t	i;

	if (!info->line[info->index])
		terminate(0, info); // endline
	i = 0;
	while (g_op_tab->name[i] && ft_strncmp(&info->line[info->index],
	g_op_tab[i].name, ft_strlen(g_op_tab[i].name)))
		i++;
	if (!g_op_tab[i].name)
		terminate(0, info);
	info->ops[info->count].opcode = i + 1;
	info->index += ft_strlen(g_op_tab[i].name);
	skip_space(info);
}

static void	parse_label(t_asm *info)
{
	size_t	i;

	i = 0;
	while (ft_strchr(LABEL_CHARS, info->line[info->index + i]))
		i++;
	if (info->line[info->index + i] != LABEL_CHAR || !i)
		return ;
	info->ops[info->count].label = ft_strndup(&info->line[info->index], i);
	info->index += i + 1;
	skip_space(info);
	// check_new_line
}

void		parse_operation(t_asm *info)
{
	size_t	n;

	if (!(info->ops = realloc(info->ops, ++info->count)))
		terminate(0, info); //memory error
	ft_bzero(&info->ops[info->count], sizeof(info->ops));
	parse_label(info);
	ft_printf("%s\n", info->ops[info->count].label); // debug
	parse_instruction(info);
	n = g_op_tab[info->ops[info->count].opcode - 1].args;
	while (n--)
		parse_arguments(info);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 12:52:14 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/05 22:16:21 by aromny-w         ###   ########.fr       */
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

static int	check_next_line(t_asm *info)
{
	int		ret;
	char	*buf;

	if (!(ret = get_next_line(info->fd, &buf)))
		return (0);
	if (ret == -1)
		terminate(-1, info); // read error
	free(info->line);
	info->line = buf;
	info->index = 0;
	info->lines++;
	skip_space(info);
	return (1);
}

static int	is_label(t_asm *info)
{
	size_t	i;

	i = 0;
	while (ft_strchr(LABEL_CHARS, info->line[info->index + i]))
		i++;
	if (info->line[info->index + i] != LABEL_CHAR)
		return (0);
	return (i);
}

static int	parse_label(t_asm *info)
{
	size_t	i;

	if (!(info->ops = realloc(info->ops, sizeof(t_cmd) * ++info->n)))
		terminate(0, info); //memory error;
	ft_bzero(&info->ops[info->n - 1], sizeof(t_cmd));
	if (!(i = is_label(info)))
		return (1);
	info->ops[info->n - 1].label = ft_strndup(&info->line[info->index], i);
	info->index += i + 1;
	skip_space(info);
	while (!info->line[info->index])
		if (!check_next_line(info))
			return (0);
	if (!is_label(info))
		return (1);
	parse_label(info);
	return (1);
}

void		parse_operation(t_asm *info)
{
	if (!parse_label(info))
		return ;
	parse_instruction(info);
	parse_arguments(info);
	set_size(info);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 12:52:14 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/10 14:29:57 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		check_next_line(t_asm *info)
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

static int		is_label(t_asm *info)
{
	size_t	i;

	i = 0;
	while (ft_strchr(LABEL_CHARS, info->line[info->index + i]))
		i++;
	if (info->line[info->index + i] != LABEL_CHAR)
		return (0);
	return (i);
}

static int		check_label(t_asm *info)
{
	size_t	i;

	if (!(i = is_label(info)))
		return (1);
	info->op->label = ft_strndup(&info->line[info->index], i);
	info->index += i + 1;
	skip_space(info);
	while (!info->line[info->index])
		if (!check_next_line(info))
			return (1);
	if (is_label(info))
		return (0);
	return (1);
}

static t_cmd	*add_new_operation(t_asm *info)
{
	t_cmd	*new;

	if (!(new = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	ft_bzero(new, sizeof(t_cmd));
	new->next = info->op;
	return (new);
}

void			parse_operation(t_asm *info)
{
	if (!(info->op = add_new_operation(info)))
		terminate(0, info); // memory error
	if (!check_label(info))
		return (parse_operation(info));
	if (!info->line[info->index])
		return ;
	parse_opcode(info);
	parse_arguments(info);
	set_size(info);
}

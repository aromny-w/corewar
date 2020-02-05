/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:44:22 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/05 15:15:46 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	check_next_line(t_asm *info)
{
	int		ret;
	char	*buf;

	if (!(ret = get_next_line(info->fd, &buf)))
		terminate(0, info);  // end (null)
	if (ret == -1)
		terminate(-1, info); // read error
	free(info->line);
	info->line = buf;
	info->index = 0;
	info->lines++;
	skip_space(info);
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

void		parse_label(t_asm *info)
{
	size_t	i;

	if (!(info->ops = realloc(info->ops, sizeof(t_cmd) * ++info->n)))
		terminate(0, info); //memory error;
	ft_bzero(&info->ops[info->n - 1], sizeof(t_cmd));
	if (!(i = is_label(info)))
		return ;
	info->ops[info->n - 1].label = ft_strndup(&info->line[info->index], i);
	info->index += i + 1;
	skip_space(info);
	while (!info->line[info->index])
		check_next_line(info);
	if (!is_label(info))
		return ;
	parse_label(info);
}

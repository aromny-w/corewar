/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 20:45:38 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/04 15:10:12 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	parse_line(t_asm *info)
{
	while (ft_isspace(info->line[info->index]))
		info->index++;
	if (!info->line[info->index] || info->line[info->index] == COMMENT_CHAR ||
	info->line[info->index] == ';')
		return ;
	else if (!ft_strncmp(info->line + info->index, NAME_CMD_STRING,
	ft_strlen(NAME_CMD_STRING)))
		parse_name(info);
	else if (!ft_strncmp(info->line + info->index, COMMENT_CMD_STRING,
	ft_strlen(COMMENT_CMD_STRING)))
		parse_comment(info);
	else
		parse_operation(info);
}

void		read_file(t_asm *info)
{
	if (read(info->fd, 0, 0) == -1)
		terminate(-1, info);
	while (get_next_line(info->fd, &info->line) == 1)
	{
		info->index = 0;
		info->lines++;
		parse_line(info);
		free(info->line);
	}
}

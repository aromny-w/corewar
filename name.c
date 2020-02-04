/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:49:05 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/04 16:50:38 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	check_string_tail(t_asm *info)
{
	skip_space(info);
	if (info->line[info->index] && info->line[info->index] != COMMENT_CHAR &&
	info->line[info->index] != ';')
		terminate(0, info); //invalid instr
	return ;
}

static int	check_next_line(t_asm *info)
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
	return (1);
}

static void	set_name(t_asm *info)
{
	size_t	i;

	i = 0;
	info->index++;
	while (info->line[info->index] != '"')
	{
		if (i == PROG_NAME_LENGTH)
			terminate(0, info); // too long
		else if (info->line[info->index])
			info->header.prog_name[i++] = info->line[info->index++];
		else if (check_next_line(info))
			info->header.prog_name[i++] = '\n';
	}
	info->index++;
	check_string_tail(info);
}

void		parse_name(t_asm *info)
{
	if (info->header.name_mark++)
		terminate(0, info);
	info->index += ft_strlen(NAME_CMD_STRING);
	skip_space(info);
	if (!info->line[info->index] || info->line[info->index] == COMMENT_CHAR ||
	info->line[info->index] == ';')
		terminate(0, info); // ENDLINE
	if (info->line[info->index] != '"')
		terminate(0, info); // invalid instr
	set_name(info);
}

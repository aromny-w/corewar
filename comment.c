/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:11:19 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/03 14:21:47 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	check_string_tail(t_asm *info)
{
	info->index++;
	while (ft_isspace(info->line[info->index]))
		info->index++;
	if (info->line[info->index] && info->line[info->index] != COMMENT_CHAR &&
	info->line[info->index] != ';')
		terminate(0, info); //invalid instr
	return ;
}

static int	check_next_line(t_asm *info)
{
	char	*buf;
	int		ret;

	if (!(ret = get_next_line(info->fd, &buf)))
		terminate(0, info);  // end (null)
	if (ret == -1)
		terminate(0, info); // read error
	free(info->line);
	info->line = buf;
	info->lines++;
	info->index = 0;
	return (1);
}

static void	set_comment(t_asm *info)
{
	size_t	i;

	i = 0;
	info->index++;
	while (info->line[info->index] != '"')
	{
		if (i == COMMENT_LENGTH)
			terminate(0, info); // too long
		else if (info->line[info->index])
			info->header.comment[i++] = info->line[info->index++];
		else if (check_next_line(info))
			info->header.comment[i++] = '\n';
	}
	check_string_tail(info);
	ft_printf("%s\n", info->header.comment); //debug
}

void		parse_comment(t_asm *info)
{
	if (info->header.comment_mark++)
		terminate(0, info);
	info->index += ft_strlen(COMMENT_CMD_STRING);
	while (ft_isspace(info->line[info->index]))
		info->index++;
	if (!info->line[info->index] || info->line[info->index] == COMMENT_CHAR ||
	info->line[info->index] == ';')
		terminate(0, info); // ENDLINE
	if (info->line[info->index] != '"')
		terminate(0, info); // invalid instr
	set_comment(info);
}

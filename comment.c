/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:11:19 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/10 23:55:21 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	check_string_tail(t_asm *info)
{
	skip_space(info);
	if (info->line[info->index] && info->line[info->index] != COMMENT_CHAR &&
	info->line[info->index] != COMMENT_CHAR_2)
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
	info->index++;
	check_string_tail(info);
}

void		parse_comment(t_asm *info)
{
	if (info->comment_mark++)
		terminate(0, info);
	info->index += ft_strlen(COMMENT_CMD_STRING);
	skip_space(info);
	if (!info->line[info->index] || info->line[info->index] == COMMENT_CHAR ||
	info->line[info->index] == COMMENT_CHAR_2)
		terminate(0, info); // ENDLINE
	if (info->line[info->index] != '"')
		terminate(0, info); // invalid instr
	set_comment(info);
}

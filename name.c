/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:49:05 by aromny-w          #+#    #+#             */
/*   Updated: 2020/01/30 20:52:55 by aromny-w         ###   ########.fr       */
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
	info->index = 0;
	return (1);
}


static void set_name(t_asm *info)
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
	check_string_tail(info);
	ft_printf("%s\n", info->header.prog_name);
}

void		parse_name(t_asm *info)
{
	if (info->name++)
		terminate(0, info);
	info->index += ft_strlen(NAME_CMD_STRING);
	while (ft_isspace(info->line[info->index]))
		info->index++;
	if (!info->line[info->index] || info->line[info->index] == COMMENT_CHAR ||
	info->line[info->index] == ';')
		terminate(0, info); // ENDLINE
	if (info->line[info->index] != '"')
		terminate(0, info); // invalid instr
	set_name(info);
}

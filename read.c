/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 20:45:38 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 18:07:16 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	reverse_commands(t_asm *info)
{
	t_cmd	*prev;
	t_cmd	*curr;
	t_cmd	*next;

	prev = NULL;
	curr = info->op;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	info->op = prev;
}

static void	parse_line(t_asm *info)
{
	skip_space(info);
	if (!info->line[info->index] || info->line[info->index] == COMMENT_CHAR ||
	info->line[info->index] == COMMENT_CHAR_2)
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
	int	ret;

	info->fd = open(info->path, O_RDONLY);
	if (read(info->fd, 0, 0) == -1)
		terminate(info, -1);
	while ((ret = get_next_line(info->fd, &info->line)) == 1)
	{
		info->index = 0;
		info->lines++;
		parse_line(info);
		free(info->line);
		info->line = NULL;
	}
	if (ret == -1)
		terminate(info, 0); // memmory erorr
	reverse_commands(info);
	parse_argcode(info);
	close(info->fd);
}

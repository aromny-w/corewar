/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 17:48:44 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/20 17:48:47 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_number(int fd, int n, size_t size)
{
	char	byte[4];

	byte[0] = n >> 0;
	byte[1] = n >> 8;
	byte[2] = n >> 16;
	byte[3] = n >> 24;
	if (size >= 4)
		write(fd, &byte[3], 1);
	if (size >= 3)
		write(fd, &byte[2], 1);
	if (size >= 2)
		write(fd, &byte[1], 1);
	if (size >= 1)
		write(fd, &byte[0], 1);
}

static void	write_line(int fd, t_line *line, t_arg *arg)
{
	int	i;

	if (line->op.opcode)
		write_number(fd, line->op.opcode, sizeof(char));
	if (line->op.pcode)
		write_number(fd, line->acb, sizeof(char));
	i = -1;
	while (++i < line->op.params)
		write_number(fd, arg[i].value, arg[i].size);
	if (line->next)
		write_line(fd, line->next, line->next->arg);
}

static void	write_header(t_header header, int fd)
{
	write_number(fd, header.magic, sizeof(int));
	write(fd, header.prog_name, PROG_NAME_LENGTH);
	write_number(fd, 0, sizeof(int));
	write_number(fd, header.prog_size, sizeof(int));
	write(fd, header.comment, COMMENT_LENGTH);
	write_number(fd, 0, sizeof(int));
}

void		bytecode_output(t_prog *info)
{
	int		fd;

	fd = open(info->filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (write(fd, NULL, 0) == -1)
		terminate(info, 0, NULL);
	ft_printf("Writing output program to %s\n", info->filename);
	write_header(info->header, fd);
	if (info->line)
		write_line(fd, info->line, info->line->arg);
	close(fd);
}

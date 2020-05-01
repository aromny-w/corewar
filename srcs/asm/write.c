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

static void	write_instr(int fd, t_instr *instr, t_arg *arg)
{
	int	i;

	if (instr->op.opcode)
		write_number(fd, instr->op.opcode, sizeof(char));
	if (instr->op.pcode)
		write_number(fd, instr->acb, sizeof(char));
	i = -1;
	while (++i < instr->op.params)
		write_number(fd, arg[i].value, arg[i].size);
	if (instr->next)
		write_instr(fd, instr->next, instr->next->arg);
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

void		write_bytecode(t_prog *info)
{
	int		fd;

	fd = open(info->filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (write(fd, NULL, 0) == -1)
		terminate(info, 0, NULL); // write error
	ft_printf("Writing output program to %s\n", info->filename);
	write_header(info->header, fd);
	write_instr(fd, info->instr, info->instr->arg);
	close(fd);
}

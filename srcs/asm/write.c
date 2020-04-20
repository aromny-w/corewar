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
	while (size--)
		ft_dprintf(fd, "%c", n >> (size * 8));
}

static void	write_instr(int fd, t_instr *instr, t_arg *arg)
{
	int	i;

	if (instr->op.opcode)
		write_number(fd, instr->op.opcode, sizeof(char));
	if (instr->op.argbyte)
		write_number(fd, (arg[0].type << 6) + (arg[1].type << 4) +
		(arg[2].type << 2) + (arg[3].type << 0), sizeof(char));
	i = -1;
	while (arg[++i].size)
		write_number(fd, arg[i].value, arg[i].size);
	if (instr->next)
		write_instr(fd, instr->next, instr->arg);
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

void		write_to_file(t_asm *info)
{
	int		fd;

	fd = open(info->filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (write(fd, NULL, 0) == -1)
		terminate(info, 0, NULL); // write error
	ft_printf("Writing output program to %s\n", info->filename);
	write_header(info->header, fd);
	write_instr(fd, info->instr, info->instr->arg);
}

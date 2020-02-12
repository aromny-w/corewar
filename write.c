/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 20:00:35 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 15:55:59 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_instruction(t_asm *info, t_cmd *op)
{
	unsigned char	buf[4];
	unsigned char	n;
	unsigned char	i;
	unsigned char	j;

	if (!op->opcode)
		return ;
	write(info->fd, &op->opcode, sizeof(op->opcode));
	if (g_op_tab[op->opcode - 1].type[0] != 2)
		write(info->fd, &op->typecode, sizeof(op->typecode));
	n = -1;
	while (++n < g_op_tab[op->opcode - 1].args)
	{
		i = 0;
		j = op->argsize[n];
		while (i < 4)
			buf[i++] = op->arg[n].byte[--j];
		write(info->fd, buf, op->argsize[n]);
	}
}

static void	write_prog_size(t_asm *info)
{
	unsigned char	buf[4];
	t_byte			value;
	unsigned char	i;
	unsigned char	j;

	value.nbr = info->header.prog_size;
	i = 0;
	j = 4;
	while (i < 4)
		buf[i++] = value.byte[--j];
	write(info->fd, buf, 4);
}

static void	write_magic(t_asm *info)
{
	unsigned char	buf[4];
	t_byte			value;
	unsigned char	i;
	unsigned char	j;

	value.nbr = info->header.magic;
	i = 0;
	j = 4;
	while (i < 4)
		buf[i++] = value.byte[--j];
	write(info->fd, buf, 4);
}

static void	write_header(t_asm *info)
{
	unsigned char	buf[4];

	ft_bzero(buf, 4);
	write_magic(info);
	write(info->fd, info->header.prog_name, PROG_NAME_LENGTH);
	write(info->fd, buf, 4);
	write_prog_size(info);
	write(info->fd, info->header.comment, COMMENT_LENGTH);
	write(info->fd, buf, 4);
}

void		write_file(t_asm *info)
{
	t_cmd	*op_ptr;
	
	info->fd = open(info->filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (write(info->fd, "", 0) == -1)
		terminate(0, info); // write error
	ft_printf("Writing output program to %s\n", info->filename);
	write_header(info);
	op_ptr = info->op;
	while (op_ptr)
	{
		write_instruction(info, op_ptr);
		op_ptr = op_ptr->next;
	}
}

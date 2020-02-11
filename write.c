/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 20:00:35 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/11 14:20:01 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_instruction(t_asm *info, t_cmd *op)
{
	unsigned char	i;

	if (!op->opcode)
		return ;
	write(info->fd, &op->opcode, sizeof(op->opcode));
	if (g_op_tab[op->opcode - 1].type[0] != 2)
		write(info->fd, &op->typecode, sizeof(op->typecode));
	i = -1;
	while (++i < g_op_tab[op->opcode - 1].args)
		write(info->fd, op->argcode[i], op->argsize[i]);
}

static void	write_header(t_asm *info)
{
	unsigned char	buf[4];
	t_byte			value;
	unsigned char	i;
	unsigned char	j;

	value.nbr = info->header.magic;
	i = 0;
	j = sizeof(info->header.magic);
	while (i < sizeof(info->header.magic))
		buf[i++] = value.byte[--j];
	write(info->fd, buf, sizeof(info->header.magic));
	write(info->fd, info->header.prog_name, PROG_NAME_LENGTH);
	ft_bzero(buf, sizeof(buf));
	write(info->fd, buf, sizeof(buf));
	value.nbr = info->header.prog_size;
	i = 0;
	j = sizeof(info->header.prog_size);
	while (i < sizeof(info->header.prog_size))
		buf[i++] = value.byte[--j];
	write(info->fd, buf, sizeof(info->header.prog_size));
	write(info->fd, info->header.comment, COMMENT_LENGTH);
	ft_bzero(buf, sizeof(buf));
	write(info->fd, buf, sizeof(buf));
}

void		write_file(t_asm *info)
{
	t_cmd	*op_ptr;
	
	info->fd = open(info->filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (write(info->fd, "", 0) == -1)
		terminate(0, info); // write error
	write_header(info);
	op_ptr = info->op;
	while (op_ptr)
	{
		write_instruction(info, op_ptr);
		op_ptr = op_ptr->next;
	}
}

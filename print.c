/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:24:29 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/11 20:56:23 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_instruction_3(t_cmd *op)
{
	unsigned char	i;

	if (g_op_tab[op->opcode - 1].type[0] != 2)
		ft_printf("%20s%-4hu%-6hu", "", op->opcode, op->typecode);
	else
		ft_printf("%20s%-10hu", "", op->opcode);
	i = -1;
	while (++i < g_op_tab[op->opcode - 1].args)
	{
		;
	}
}

static void	print_instruction_2(t_cmd *op)
{
	unsigned char	i;

	if (g_op_tab[op->opcode - 1].type[0] != 2)
		ft_printf("%20s%-4hu%-6hu", "", op->opcode, op->typecode);
	else
		ft_printf("%20s%-10hu", "", op->opcode);
	i = -1;
	while (++i < g_op_tab[op->opcode - 1].args)
	{
		if (op->argsize[i] == 1)
			ft_printf("%-18hhu", op->argcode[i][0]);
		else if (op->argsize[i] == 2)
			ft_printf("%-3hhu %-14hhu", op->argcode[i][0], op->argcode[i][1]);
		else
			ft_printf("%-3hhu %-3hhu %-3hhu %-6hhu", op->argcode[i][0],
			op->argcode[i][1], op->argcode[i][2], op->argcode[i][3]);
	}
	ft_printf("\n");
}

static void	print_instruction(t_cmd *op)
{
	unsigned char	i;

	if (op->label)
		ft_printf("%-10hu :    %s:\n", op->pos, op->label);
	if (!op->opcode)
		return ;
	ft_printf("%-4hu (%-3hu) :        %-10s", op->pos, op->opsize, op->name);
	i = -1;
	while (++i < g_op_tab[op->opcode - 1].args)
		ft_printf("%-18s", op->arg[i]);
	ft_printf("\n");
	print_instruction_2(op);
	print_instruction_3(op);
}

static void	write_header(t_asm *info)
{
	ft_printf("Program size : %u bytes\n", info->header.prog_size);
	ft_printf("Name : \"%s\"\n", info->header.prog_name);
	ft_printf("Comment : \"%s\"\n", info->header.comment);
	ft_printf("\n");
}

void		print_stdout(t_asm *info)
{
	t_cmd	*op_ptr;

	ft_printf("Dumping annotated program on standard output\n");
	write_header(info);
	op_ptr = info->op;
	while (op_ptr)
	{
		print_instruction(op_ptr);
		op_ptr = op_ptr->next;
	}
}

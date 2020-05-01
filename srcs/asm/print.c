/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 19:03:50 by student           #+#    #+#             */
/*   Updated: 2020/04/26 19:03:51 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_ints(t_instr *instr, t_arg *arg)
{
	int	i;

	i = -1;
	ft_printf("%-3u ", instr->op.opcode);
	instr->op.pcode ? ft_printf("%-3u   ", instr->acb) : ft_printf("      ");
	while (++i < instr->op.params)
		ft_printf("%-18d", arg[i].value);
}

static void	print_bytecode(t_instr *instr, t_arg *arg)
{
	int i;

	i = -1;
	ft_printf("%-3u ", instr->op.opcode);
	instr->op.pcode ? ft_printf("%-3u   ", instr->acb) : ft_printf("      ");
	while (++i < instr->op.params)
	{
		if (arg[i].size == 4)
			ft_printf("%-3u %-3u %-3u %-3u   ", arg[i].value >> 24 & 255,
			arg[i].value >> 16 & 255, arg[i].value >> 8 & 255,
			arg[i].value >> 0 & 255);
		if (arg[i].size == 2)
			ft_printf("%-3u %-3u           ", arg[i].value >> 8 & 255,
			arg[i].value >> 0 & 255);
		if (arg[i].size == 1)
			ft_printf("%-3u               ", arg[i].value >> 0 & 255);
	}
}

static void	print_instr(t_instr *instr, t_arg *arg)
{
	int	i;

	if (instr->label)
		ft_printf("%-4u       :    %s\n", instr->pos, arg[3].token->content);
	if (instr->op.name)
	{
		ft_printf("%-4u (%-3u) :        %-10s", instr->pos, instr->size,
		instr->op.name);
		i = -1;
		while (++i < instr->op.params)
			ft_printf("%-18s", instr->arg[i].token->content);
		ft_printf("\n");
		ft_printf("                    ");
		print_bytecode(instr, arg);
		ft_printf("\n");
		ft_printf("                    ");
		print_ints(instr, arg);
		ft_printf("\n");
		ft_printf("\n");
	}
}

static void	print_header(t_header header)
{
	ft_printf("Program size : %u bytes\n", header.prog_size);
	ft_printf("Name : \"%s\"\n", header.prog_name);
	ft_printf("Comment : \"%s\"\n", header.comment);
	ft_printf("\n");
}

void		print_annotation(t_prog *info)
{
	t_instr *instr;

	instr = info->instr;
	ft_printf("Dumping annotated program on standard output\n");
	print_header(info->header);
	while (instr)
	{
		print_instr(instr, instr->arg);
		instr = instr->next;
	}
}

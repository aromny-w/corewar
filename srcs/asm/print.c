/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 19:03:50 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/26 19:03:51 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_ints(t_line *line, t_arg *arg)
{
	int	i;

	i = -1;
	ft_printf("%-3u ", line->op.opcode);
	line->op.pcode ? ft_printf("%-3u   ", line->acb) : ft_printf("      ");
	while (++i < line->op.params)
		ft_printf("%-18d", arg[i].value);
}

static void	print_bytecode(t_line *line, t_arg *arg)
{
	int i;

	i = -1;
	ft_printf("%-3u ", line->op.opcode);
	line->op.pcode ? ft_printf("%-3u   ", line->acb) : ft_printf("      ");
	while (++i < line->op.params)
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

static void	print_line(t_line *line, t_arg *arg)
{
	int	i;

	if (line->label)
		ft_printf("%-4u       :    %s\n", line->pos, line->label->content);
	if (line->op.name)
	{
		ft_printf("%-4u (%-3u) :        %-10s", line->pos, line->size,
		line->op.name);
		i = -1;
		while (++i < line->op.params)
			ft_printf("%-18s", line->arg[i].token->content);
		ft_printf("\n");
		ft_printf("                    ");
		print_bytecode(line, arg);
		ft_printf("\n");
		ft_printf("                    ");
		print_ints(line, arg);
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

void		annotated_output(t_exec *info)
{
	t_line *line;

	line = info->line;
	ft_printf("Dumping annotated program on standard output\n");
	print_header(info->header);
	while (line)
	{
		print_line(line, line->arg);
		line = line->next;
	}
}

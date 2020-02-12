/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argcode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:41:03 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 15:10:24 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static short	get_label_pos(t_asm *info, char *str)
{
	t_cmd	*op_ptr;

	op_ptr = info->op;
	if (*str == DIRECT_CHAR)
		str++;
	if (*str == LABEL_CHAR)
		str++;
	while (op_ptr)
	{
		if (op_ptr->label && !ft_strcmp(op_ptr->label, str))
			break ;
		op_ptr = op_ptr->next;
	}
	if (!op_ptr)
		terminate(0, info); // label not found
	return (op_ptr->pos);
}

static int	get_argcode(t_asm *info, t_cmd *op, size_t i)
{
	if (op->type[i] == T_REG)
		return (ft_atoi(op->argbuf[i] + 1));
	else if (op->type[i] == T_DIR && op->argbuf[i][1] != LABEL_CHAR)
		return (ft_atoi(op->argbuf[i] + 1));
	else if (op->type[i] == T_DIR)
		return (get_label_pos(info, op->argbuf[i]) - op->pos);
	else if (op->type[i] == T_IND && op->argbuf[i][0] != LABEL_CHAR)
		return (ft_atoi(op->argbuf[i]));
	else if (op->type[i] == T_IND)
		return (get_label_pos(info, op->argbuf[i]) - op->pos);
	return (0);
}

void		parse_argcode(t_asm *info)
{
	unsigned char	i;
	t_cmd			*op_ptr;

	op_ptr = info->op;
	while (op_ptr)
	{
		i = -1;
		if (op_ptr->opcode)
			while (++i < g_op_tab[op_ptr->opcode - 1].args)
				op_ptr->arg[i].nbr = get_argcode(info, op_ptr, i);
		op_ptr = op_ptr->next;
	}
}

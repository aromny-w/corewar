/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argcode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:41:03 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/10 21:54:54 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static short			get_label_pos(t_asm *info, char *str)
{
	t_cmd			*op_ptr;
	unsigned char	i;

	op_ptr = info->op;
	i = 0;
	if (str[i] == DIRECT_CHAR)
		i++;
	if (str[i] == LABEL_CHAR)
		i++;
	while (op_ptr)
	{
		if (op_ptr->label && !ft_strcmp(op_ptr->label, str + i))
			break ;
		op_ptr = op_ptr->next;
	}
	if (!op_ptr)
		terminate(0, info); // label not found
	return (op_ptr->pos);
}

static unsigned char	*get_label_value(t_asm *info, t_cmd *op, size_t n)
{
	unsigned char	*code;
	t_byte			value;
	unsigned char	i;
	unsigned char	j;

	if (!(code = (unsigned char *)malloc(sizeof(unsigned char) *
	op->argsize[n])))
		terminate(0, info); // memory error;
	value.nbr = get_label_pos(info, op->arg[n]) - op->pos;
	i = 0;
	j = 4;
	while (i < op[n].argsize[n])
		code[i++] = value.byte[j--];
	return (code);
}

static unsigned char	*get_nbr_value(t_asm *info, char *str, char size)
{
	unsigned char	*code;
	t_byte			value;
	unsigned char	i;
	unsigned char	j;

	if (!(code = (unsigned char *)malloc(sizeof(unsigned char) * size)))
		terminate(0, info); // memory error
	value.nbr = ft_atoi(str);
	i = 0;
	j = 4;
	while (i < size)
		code[i++] = value.byte[j--];
	return (code);
}

static unsigned char	*get_argcode(t_asm *info, t_cmd *op, size_t i)
{
	if (op->type[i] == T_REG)
		return (get_nbr_value(info, op->arg[i] + 1, op->argsize[i]));
	else if (op->type[i] == T_DIR && op->arg[i][1] != LABEL_CHAR)
		return (get_nbr_value(info, op->arg[i] + 1, op->argsize[i]));
	else if (op->type[i] == T_DIR)
		return (get_label_value(info, op, i));
	else if (op->type[i] == T_IND && op->arg[i][0] != LABEL_CHAR)
		return (get_nbr_value(info, op->arg[i], op->argsize[i]));
	else if (op->type[i] == T_IND)
		return (get_label_value(info, op, i));
	return (NULL);
}

void					parse_argcode(t_asm *info)
{
	unsigned char	i;
	t_cmd			*op_ptr;

	op_ptr = info->op;
	while (op_ptr)
	{
		i = -1;
		if (op_ptr->opcode)
			while (++i < g_op_tab[op_ptr->opcode - 1].args)
				op_ptr->argcode[i] = get_argcode(info, op_ptr, i);
		op_ptr = op_ptr->next;
	}
}

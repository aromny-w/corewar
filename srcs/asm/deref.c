/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deref.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 11:34:30 by student           #+#    #+#             */
/*   Updated: 2020/04/09 11:34:34 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	set_arg_value(t_prog *info, t_instr **instr, t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < (*instr)->op.params)
	{
		if (arg[i].token->type == INDIRECT)
			arg[i].value = ft_atoi(arg[i].token->content);
		if (arg[i].token->type == REGISTER || arg[i].token->type == DIRECT)
			arg[i].value = ft_atoi(arg[i].token->content + 1);
		if (arg[i].token->type == DIRECT_LABEL ||
		arg[i].token->type == INDIRECT_LABEL)
			arg[i].value = get_label_pos(info, arg[i].token) - (*instr)->pos;
	}
	if ((*instr)->next)
		set_arg_value(info, &(*instr)->next, (*instr)->next->arg);
}

static void	set_size_and_pos(t_prog *info, t_instr **instr, unsigned int pos)
{
	int	i;

	if ((*instr)->op.name)
		(*instr)->size += 1;
	if ((*instr)->op.pcode)
		(*instr)->size += 1;
	i = -1;
	while (++i < (*instr)->op.params)
	{
		if ((*instr)->arg[i].type == T_REG)
			(*instr)->arg[i].size = sizeof(char);
		else if ((*instr)->arg[i].type == T_IND)
			(*instr)->arg[i].size = sizeof(short);
		else if ((*instr)->arg[i].type == T_DIR && !(*instr)->op.idx)
			(*instr)->arg[i].size = sizeof(int);
		else if ((*instr)->arg[i].type == T_DIR)
			(*instr)->arg[i].size = sizeof(short);
		(*instr)->size += (*instr)->arg[i].size;
	}
	(*instr)->pos = pos;
	info->header.prog_size += (*instr)->size;
	if ((*instr)->next)
		set_size_and_pos(info, &(*instr)->next, (*instr)->pos + (*instr)->size);
}

static void	set_acb(t_prog *info, t_instr **instr, t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < (*instr)->op.params)
	{
		if (arg[i].type == T_REG)
			(*instr)->acb += REG_CODE << (8 - (i + 1) * 2);
		if (arg[i].type == T_DIR)
			(*instr)->acb += DIR_CODE << (8 - (i + 1) * 2);
		if (arg[i].type == T_IND)
			(*instr)->acb += IND_CODE << (8 - (i + 1) * 2);
	}
	if ((*instr)->next)
		set_acb(info, &(*instr)->next, (*instr)->next->arg);
}

static void	set_arg_type(t_prog *info, t_instr **instr, t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < (*instr)->op.params)
	{
		if (arg[i].token->type == REGISTER)
			arg[i].type = T_REG;
		if (arg[i].token->type == DIRECT || arg[i].token->type == DIRECT_LABEL)
			(*instr)->arg[i].type = T_DIR;
		if (arg[i].token->type == INDIRECT ||
		arg[i].token->type == INDIRECT_LABEL)
			(*instr)->arg[i].type = T_IND;
		if (!(arg[i].type & (*instr)->op.type[i]))
			terminate(info, 0, (*instr)->arg[i].token); // invlid argument
	}
	if ((*instr)->next)
		set_arg_type(info, &(*instr)->next, (*instr)->next->arg);
}

void		dereference_tokens(t_prog *info)
{
	set_arg_type(info, &info->instr, info->instr->arg);
	set_acb(info, &info->instr, info->instr->arg);
	set_size_and_pos(info, &info->instr, 0);
	set_arg_value(info, &info->instr, info->instr->arg);
}

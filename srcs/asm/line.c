/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deref.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 11:34:30 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/09 11:34:34 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	set_arg_value(t_prog *info, t_line **line, t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < (*line)->op.params)
	{
		if (arg[i].token->type == INDIRECT)
			arg[i].value = ft_atoi(arg[i].token->str);
		if (arg[i].token->type == REGISTER || arg[i].token->type == DIRECT)
			arg[i].value = ft_atoi(arg[i].token->str + 1);
		if (arg[i].token->type == DIRECT_LABEL)
			arg[i].ref = arg[i].token->str + 2;
		if (arg[i].token->type == INDIRECT_LABEL)
			arg[i].ref = arg[i].token->str + 1;
	}
	if ((*line)->next)
		set_arg_value(info, &(*line)->next, (*line)->next->arg);
}

static void	set_size_and_pos(t_prog *info, t_line **line, unsigned int pos)
{
	int	i;

	if ((*line)->op.name)
		(*line)->size += 1;
	if ((*line)->op.pcode)
		(*line)->size += 1;
	i = -1;
	while (++i < (*line)->op.params)
	{
		if ((*line)->arg[i].type == T_REG)
			(*line)->arg[i].size = sizeof(char);
		else if ((*line)->arg[i].type == T_IND)
			(*line)->arg[i].size = sizeof(short);
		else if ((*line)->arg[i].type == T_DIR && !(*line)->op.idx)
			(*line)->arg[i].size = sizeof(int);
		else if ((*line)->arg[i].type == T_DIR)
			(*line)->arg[i].size = sizeof(short);
		(*line)->size += (*line)->arg[i].size;
	}
	(*line)->pos = pos;
	info->header.prog_size += (*line)->size;
	if ((*line)->next)
		set_size_and_pos(info, &(*line)->next, (*line)->pos + (*line)->size);
}

static void	set_acb(t_prog *info, t_line **line, t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < (*line)->op.params)
	{
		if (arg[i].type == T_REG)
			(*line)->acb += REG_CODE << (8 - (i + 1) * 2);
		if (arg[i].type == T_DIR)
			(*line)->acb += DIR_CODE << (8 - (i + 1) * 2);
		if (arg[i].type == T_IND)
			(*line)->acb += IND_CODE << (8 - (i + 1) * 2);
	}
	if ((*line)->next)
		set_acb(info, &(*line)->next, (*line)->next->arg);
}

static void	set_arg_type(t_prog *info, t_line **line, t_arg *arg)
{
	int	i;

	i = -1;
	while (arg[++i].token)
	{
		if (arg[i].token->type == REGISTER)
			arg[i].type = T_REG;
		if (arg[i].token->type == DIRECT || arg[i].token->type == DIRECT_LABEL)
			(*line)->arg[i].type = T_DIR;
		if (arg[i].token->type == INDIRECT ||
		arg[i].token->type == INDIRECT_LABEL)
			(*line)->arg[i].type = T_IND;
		if (!(arg[i].type & (*line)->op.type[i]))
			terminate(info, 11 + i, *line);
	}
	if (i != (*line)->op.params)
		terminate(info, 7, *line);
	if ((*line)->next)
		set_arg_type(info, &(*line)->next, (*line)->next->arg);
}

void		parse_lines(t_prog *info)
{
	if (!info->line)
		return ;
	set_arg_type(info, &info->line, info->line->arg);
	set_acb(info, &info->line, info->line->arg);
	set_size_and_pos(info, &info->line, 0);
	set_arg_value(info, &info->line, info->line->arg);
	dereference_labels(info);
}

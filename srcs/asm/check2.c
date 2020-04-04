/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 05:08:45 by student           #+#    #+#             */
/*   Updated: 2020/04/05 01:16:48 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	instruction_check(t_asm *info, size_t *i)
{
	if (info->token[*i].type == ENDLINE || (info->token[*i].type == LABEL &&
	info->token[++(*i)].type == ENDLINE))
		return ;
	if (info->token[*i].type != INSTRUCTION)
		terminate(info, 0, &info->token[*i]);
	(*i)++;
	if (!(info->token[*i].type > 3 && info->token[*i].type < 9))
		terminate(info, 0, &info->token[*i]);
	while (info->token[++(*i)].type != ENDLINE)
	{
		if (info->token[*i].type != SEPARATOR)
			terminate(info, 0, &info->token[*i]);
		(*i)++;
		if (!(info->token[*i].type > 3 && info->token[*i].type < 9))
			terminate(info, 0, &info->token[*i]);
	}
}

static void	header_check(t_asm *info, bool *prog_name, bool *comment, size_t *i)
{
	if (info->token[++(*i)].type == ENDLINE)
		return ;
	else if (!ft_strcmp(info->token[*i].content, NAME_CMD_STRING) &&
	!*prog_name)
		*prog_name = true;
	else if (!ft_strcmp(info->token[*i].content, COMMENT_CMD_STRING) &&
	!*comment)
		*comment = true;
	else
		terminate(info, 0, &info->token[*i]);
	if (info->token[++(*i)].type != STRING)
		terminate(info, 0, &info->token[*i]);
	if (info->token[++(*i)].type != ENDLINE)
		terminate(info, 0, &info->token[*i]);
}

void		syntax_check(t_asm *info)
{
	bool	prog_name;
	bool	comment;
	size_t	i;

	i = -1;
	prog_name = false;
	comment = false;
	while (!(prog_name && comment))
		header_check(info, &prog_name, &comment, &i);
	while (info->token[++i].type != END)
		instruction_check(info, &i);
}

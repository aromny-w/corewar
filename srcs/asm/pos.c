/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:30:52 by student           #+#    #+#             */
/*   Updated: 2020/04/27 16:30:53 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned int	get_label_pos(t_prog *info, t_token *token)
{
	t_instr	*instr;
	char	*label;

	instr = info->instr;
	label = token->content + (token->type == DIRECT_LABEL ? 2 : 1);
	while (instr)
	{
		if (instr->label)
			if (!ft_strcmp(label, instr->label))
				break ;
		instr = instr->next;
	}
	if (!instr)
		terminate(info, 0, token); // failed to dereference
	return (instr->pos);
}

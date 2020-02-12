/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:07:56 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 18:06:20 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	delete_commands(t_cmd **op)
{
	t_cmd			*tmp;
	t_cmd			*next;
	unsigned char	i;

	tmp = *op;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->label);
		i = -1;
		if (tmp->opcode)
			while (++i < g_op_tab[tmp->opcode - 1].args)
				free(tmp->argbuf[i]);
		free(tmp);
		tmp = next;
	}
	*op = NULL;
}

void		destroy_struct(t_asm *info)
{
	free(info->filename);
	if (info->line)
		free(info->line);
	delete_commands(&info->op);
	ft_bzero(info, sizeof(info));
}

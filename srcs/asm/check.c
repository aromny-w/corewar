/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 16:44:15 by student           #+#    #+#             */
/*   Updated: 2020/03/25 21:25:53 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	instruction_check(t_asm *info, t_token token)
{
	size_t	i;

	i = -1;
	while (g_op_tab[++i].op)
		if (!ft_strcmp(token.content, g_op_tab[i].op))
			break ;
	if (!g_op_tab[i].op)
		terminate(info, 0); // invalid inst
}

void		lexical_check(t_asm *info, t_token token)
{
	if (token.type == INSTRUCTION)
		instruction_check(info, token);
}

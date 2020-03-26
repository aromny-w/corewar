/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 16:44:15 by student           #+#    #+#             */
/*   Updated: 2020/03/26 22:04:43 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	number_check(t_asm *info, t_token token)
{
	size_t i;

	i = -1;
	if (token.type == REGISTER || token.type == DIRECT)
		i++;
	if (ft_isdigit(token.content[i + 1]))
	{
		while (ft_isdigit(token.content[++i]))
			continue ;
		if (!token.content[i])
			return ;
	}
	token.col += i;
	terminate(info, 0); // lexical error
}

static void	instruction_check(t_asm *info, t_token token)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (ft_islower(token.content[++i]))
		continue ;
	j = -1;
	if (!token.content[i])
		while (g_op_tab[++j].op)
			if (!ft_strcmp(token.content, g_op_tab[j].op))
				break ;
	if (!token.content[i] && g_op_tab[j].op)
		return ;
	if (!token.content[i] && !g_op_tab[j].op)
		terminate(info, 0); // invalid inst
	token.col += i;
	terminate(info, 0); // lexical error
}

static void	label_check(t_asm *info, t_token token)
{
	char	c;
	size_t	i;

	c = token.type == LABEL ? LABEL_CHAR : 0;
	i = -1;
	if (token.type == INDIRECT_LABEL)
		i += 1;
	else if (token.type == DIRECT_LABEL)
		i += 2;
	if (token.content[i + 1])
	{
		while (token.content[++i] != c)
			if (!ft_strchr(LABEL_CHARS, token.content[i]))
				break ;
		if (token.content[i] == c)
			return ;
	}
	token.col += i;
	terminate(info, 0); // lexical error
}

void		lexical_check(t_asm *info, t_token token)
{
	if (token.type != LABEL && token.type != INSTRUCTION &&
	token.type != REGISTER && token.type != DIRECT &&
	token.type != DIRECT_LABEL && token.type != INDIRECT &&
	token.type != INDIRECT_LABEL)
		return ;
	else if (token.type == LABEL || token.type == DIRECT_LABEL ||
	token.type == INDIRECT_LABEL)
		label_check(info, token);
	else if (token.type == INSTRUCTION)
		instruction_check(info, token);
	else
		number_check(info, token);
}

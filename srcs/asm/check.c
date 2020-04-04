/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 16:44:15 by student           #+#    #+#             */
/*   Updated: 2020/04/03 17:35:55 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	number_check(t_asm *info, t_token token)
{
	size_t i;

	i = -1;
	if (token.type == REGISTER || token.type == DIRECT)
		i++;
	if (token.type != REGISTER)
		if (token.content[i + 1] == '+' || token.content[i + 1] == '-')
			i++;
	if (ft_isdigit(token.content[i + 1]))
	{
		while (ft_isdigit(token.content[++i]))
			continue ;
		if (!token.content[i])
			return ;
	}
	token.col += i;
	terminate(info, 0, &token); // lexical error
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
		terminate(info, 0, &token); // invalid inst
	token.col += i;
	terminate(info, 0, &token); // lexical error
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
	terminate(info, 0, &token); // lexical error
}

static void	command_check(t_asm *info, t_token token)
{
	size_t	i;

	i = 0;
	while (ft_islower(token.content[++i]))
		continue ;
	if (!token.content[i])
	{
		if (!ft_strcmp(token.content, NAME_CMD_STRING) ||
		!ft_strcmp(token.content, COMMENT_CMD_STRING))
			return ;
		terminate(info, 0, &token); // invalid command
	}
	token.col += i;
	terminate(info, 0, &token); // lexical error
}

void		lexical_check(t_asm *info, t_token token)
{
	size_t	i;

	if (token.type == COMMAND)
		return (command_check(info, token));
	if (token.type == INSTRUCTION)
		return (instruction_check(info, token));
	if (token.type == LABEL || token.type == DIRECT_LABEL ||
	token.type == INDIRECT_LABEL)
		return (label_check(info, token));
	if (token.type == REGISTER || token.type == DIRECT ||
	token.type == INDIRECT)
		return (number_check(info, token));
	if (token.type != STRING ||
	token.content[i = ft_strlen(token.content) - 1] == STRING_CHAR)
		return ;
	token.col += i;
	terminate(info, 0, &token); // lexical error
}

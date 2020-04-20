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

static void	number_check(t_asm *info)
{
	size_t i;

	i = -1;
	if (info->token->type == REGISTER || info->token->type == DIRECT)
		i += 1;
	if (info->token->type != REGISTER)
		if (info->token->content[i + 1] == '+' ||
		info->token->content[i + 1] == '-')
			i += 1;
	if (ft_isdigit(info->token->content[i + 1]))
	{
		while (ft_isdigit(info->token->content[++i]))
			continue ;
		if (!info->token->content[i])
			return ;
	}
	info->token->col += i;
	terminate(info, 0, NULL); // lexical error
}

static void	string_check(t_asm *info)
{
	char	*str;
	size_t	i;

	i = ft_strlen(info->token->content) - 1;
	if (info->token->content[i] == STRING_CHAR)
		return ;
	str = info->token->content;
	while (*str++)
	{
		info->token->col++;
		if (*str != '\n')
			continue ;
		info->token->col = 0;
		info->token->row++;
	}
	terminate(info, 0, NULL); // lexical error
}

static void	general_check(t_asm *info, char c)
{
	size_t	i;

	i = -1;
	if (info->token->type == DIRECT_LABEL)
		i += 1;
	if (info->token->type == INDIRECT_LABEL)
		i += 2;
	if (info->token->content[i + 1])
	{
		while (ft_strchr(LABEL_CHARS, info->token->content[++i]))
			continue ;
		if (info->token->content[i] == c)
			return ;
	}
	info->token->col += i;
	terminate(info, 0, NULL); // lexical error
}

void		lexical_check(t_asm *info)
{
	if (info->token->type == INSTRUCTION || info->token->type == DIRECT_LABEL ||
	info->token->type == INDIRECT_LABEL)
		general_check(info, '\0');
	if (info->token->type == LABEL)
		general_check(info, LABEL_CHAR);
	if (info->token->type == STRING)
		string_check(info);
	if (info->token->type == REGISTER || info->token->type == DIRECT ||
	info->token->type == INDIRECT)
		number_check(info);
}

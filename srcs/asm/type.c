/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 22:18:58 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/01 22:12:34 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static bool		is_indirect(char *s)
{
	if (*s == '+' || *s == '-')
		s++;
	while (ft_isdigit(*s++))
		if (!*s)
			return (true);
	return (false);
}

static bool		is_register(char *s)
{
	if (ft_strlen(s) > 3 || *s++ != REG_CHAR || !ft_isdigit(*s++))
		return (false);
	while (ft_isdigit(*s))
		s++;
	if (!*s)
		return (true);
	return (false);
}

static t_type	get_command_type(char *s)
{
	if (!ft_strcmp(s, NAME_CMD_STRING))
		return (COMMAND_NAME);
	if (!ft_strcmp(s, COMMENT_CMD_STRING))
		return (COMMAND_COMMENT);
	return (0);
}

t_type			get_token_type(char *s)
{
	if (!s)
		return (END);
	if (*s == '\n')
		return (ENDLINE);
	if (*s == COMMAND_CHAR)
		return (get_command_type(s));
	if (*s == STRING_CHAR)
		return (STRING);
	if (*s == SEPARATOR_CHAR)
		return (SEPARATOR);
	if (is_register(s))
		return (REGISTER);
	if (*s == DIRECT_CHAR)
		return (*(s + 1) == LABEL_CHAR ? DIRECT_LABEL : DIRECT);
	if (is_indirect(s))
		return (INDIRECT);
	if (*s == LABEL_CHAR)
		return (INDIRECT_LABEL);
	if (*s == COMMENT_CHAR || *s == COMMENT_CHAR_2)
		return (COMMENT);
	if (ft_isspace(*s))
		return (WHITESPACE);
	if (s[ft_strlen(s) - 1] == LABEL_CHAR)
		return (LABEL);
	return (INSTRUCTION);
}

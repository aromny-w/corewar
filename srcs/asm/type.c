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

static bool	is_register(char *s)
{
	if (ft_strlen(s) > 3 || *s++ != REG_CHAR || !ft_isdigit(*s++))
		return (false);
	while (ft_isdigit(*s))
		s++;
	if (!*s)
		return (true);
	return (false);
}

t_type		get_token_type(char *s)
{
	if (!s)
		return (END);
	if (!ft_strcmp(s, NAME_CMD_STRING))
		return (COMMAND_NAME);
	if (!ft_strcmp(s, COMMENT_CMD_STRING))
		return (COMMAND_COMMENT);
	if (*s == STRING_CHAR)
		return (STRING);
	if (is_register(s))
		return (REGISTER);
	if (*s == DIRECT_CHAR)
		return (*(s + 1) == LABEL_CHAR ? DIRECT_LABEL : DIRECT);
	if (ft_isdigit(*s) || *s == '-' || *s == LABEL_CHAR)
		return (*s == LABEL_CHAR ? INDIRECT_LABEL : INDIRECT);
	if (*s == '\n')
		return (ENDLINE);
	if (*s == SEPARATOR_CHAR)
		return (SEPARATOR);
	if (*s == COMMENT_CHAR || *s == COMMENT_CHAR_2)
		return (COMMENT);
	if (ft_isspace(*s))
		return (WHITESPACE);
	if (s[ft_strlen(s) - 1] == LABEL_CHAR)
		return (LABEL);
	return (INSTRUCTION);
}

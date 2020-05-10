/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 22:18:58 by student           #+#    #+#             */
/*   Updated: 2020/04/01 22:12:34 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static bool		is_indirect(char *content)
{
	if (*content == '-')
		content++;
	while (ft_isdigit(*content++))
		if (!*content)
			return (true);
	return (false);
}

static bool		is_register(char *content)
{
	if (*content++ == REG_CHAR)
	{
		while (ft_isdigit(*content))
			content++;
		if (!*content)
			return (true);
	}
	return (false);
}

static t_type	get_command_type(char *content)
{
	if (!ft_strcmp(content, NAME_CMD_STRING))
		return (COMMAND_NAME);
	if (!ft_strcmp(content, COMMENT_CMD_STRING))
		return (COMMAND_COMMENT);
	return (0);
}

t_type			get_token_type(char *content)
{
	if (!content)
		return (END);
	if (*content == '\n')
		return (ENDLINE);
	if (*content == COMMAND_CHAR)
		return (get_command_type(content));
	if (*content == STRING_CHAR)
		return (STRING);
	if (*content == SEPARATOR_CHAR)
		return (SEPARATOR);
	if (is_register(content))
		return (REGISTER);
	if (*content == DIRECT_CHAR)
		return (*(content + 1) == LABEL_CHAR ? DIRECT_LABEL : DIRECT);
	if (is_indirect(content))
		return (INDIRECT);
	if (*content == LABEL_CHAR)
		return (INDIRECT_LABEL);
	if (*content == COMMENT_CHAR || *content == COMMENT_CHAR_2)
		return (COMMENT);
	if (ft_isspace(*content))
		return (WHITESPACE);
	if (content[ft_strlen(content) - 1] == LABEL_CHAR)
		return (LABEL);
	return (INSTRUCTION);
}

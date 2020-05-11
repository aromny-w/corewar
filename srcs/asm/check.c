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

static bool	is_parameter(char type)
{
	if (type == REGISTER || type == DIRECT || type == DIRECT_LABEL ||
	type == INDIRECT || type == INDIRECT_LABEL)
		return (true);
	return (false);
}

static void	line_check(t_prog *info, t_token **token)
{
	if ((*token)->type == LABEL && (*token = (*token)->next)->type == ENDLINE)
		return ;
	if ((*token)->type != INSTRUCTION)
		terminate(info, 4, *token);
	if (!is_parameter((*token = (*token)->next)->type))
		terminate(info, 4, *token);
	while ((*token = (*token)->next)->type != ENDLINE)
	{
		if ((*token)->type == END)
			terminate(info, 3, NULL);
		if ((*token)->type != SEPARATOR)
			terminate(info, 4, *token);
		if (!is_parameter((*token = (*token)->next)->type))
			terminate(info, 4, *token);
	}
}

static void	header_check(t_prog *info, t_token **token)
{
	bool	prog_name;
	bool	comment;

	prog_name = false;
	comment = false;
	while (!prog_name || !comment)
	{
		if (!((*token)->type == COMMAND_NAME && (prog_name = !prog_name)) &&
		!((*token)->type == COMMAND_COMMENT && (comment = !comment)))
			terminate(info, 4, *token);
		if (((*token) = (*token)->next)->type != STRING)
			terminate(info, 4, *token);
		if (((*token) = (*token)->next)->type != ENDLINE)
			terminate(info, 4, *token);
		if (!prog_name || !comment)
			*token = (*token)->next;
	}
}

void		syntax_check(t_prog *info)
{
	t_token	*tptr;

	tptr = info->token;
	header_check(info, &tptr);
	if (tptr->next->type == END)
		terminate(info, 4, tptr->next);
	while ((tptr = tptr->next)->type != END)
	{
		line_check(info, &tptr);
		if (tptr->type == END)
			terminate(info, 4, tptr);
	}
}

void		lexical_check(t_prog *info, char *s)
{
	if (!ft_strncmp(s, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return ;
	if (!ft_strncmp(s, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		return ;
	if (*s == STRING_CHAR || *s == SEPARATOR_CHAR)
		return ;
	if (ft_strchr(LABEL_CHARS, *s))
		return ;
	if ((*s == '+' || *s == '-' || *s == DIRECT_CHAR) && ft_isdigit(*(s + 1)))
		return ;
	if (*s == DIRECT_CHAR && (*(s + 1) == '-' || *(s + 1) == '+') &&
	ft_isdigit(*(s + 2)))
		return ;
	if (*s == LABEL_CHAR && ft_strchr(LABEL_CHARS, *(s + 1)))
		return ;
	if ((*s == DIRECT_CHAR && *(s + 1) == LABEL_CHAR &&
	ft_strchr(LABEL_CHARS, *(s + 2))))
		return ;
	if (*s == COMMENT_CHAR || *s == COMMENT_CHAR_2)
		return ;
	if (ft_isspace(*s))
		return ;
	terminate(info, 2, info->token);
}

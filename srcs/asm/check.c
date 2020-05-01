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

static void	instr_check(t_prog *info, t_token **token)
{
	int	i;

	if ((*token)->type != INSTRUCTION)
		terminate(info, 0, *token);
	if (!is_parameter(((*token) = (*token)->next)->type))
		terminate(info, 0, *token);
	i = -1;
	while (++i < MAX_ARGS_NUMBER && (*token = (*token)->next)->type != ENDLINE)
	{
		if ((*token)->type != SEPARATOR)
			terminate(info, 0, *token);
		if (!is_parameter((*token = (*token)->next)->type))
			terminate(info, 0, *token);
	}
}

static void	header_check(t_prog *info, t_token **token)
{
	bool	prog_name;
	bool	comment;

	prog_name = false;
	comment = false;
	while (!(prog_name && comment))
	{
		while ((*token)->type == ENDLINE)
			*token = (*token)->next;
		if ((*token)->type == COMMAND_NAME && !prog_name)
			prog_name = true;
		else if ((*token)->type == COMMAND_COMMENT && !comment)
			comment = true;
		else
			terminate(info, 0, *token);
		if ((*token = (*token)->next)->type != STRING)
			terminate(info, 0, *token);
		if ((*token = (*token)->next)->type != ENDLINE)
			terminate(info, 0, *token);
	}
}

void		syntax_check(t_prog *info)
{
	t_token	*token_ptr;

	token_ptr = info->token;
	header_check(info, &token_ptr);
	while ((token_ptr = token_ptr->next)->type != END)
	{
		if (token_ptr->type == ENDLINE || (token_ptr->type == LABEL &&
		(token_ptr = token_ptr->next)->type == ENDLINE))
			continue ;
		instr_check(info, &token_ptr);
	}
}

void		lexical_check(t_prog *info)
{
	char	*str;

	str = &info->data[info->token->row][info->token->col];
	if (!ft_strncmp(str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return ;
	if (!ft_strncmp(str, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		return ;
	if (*str == STRING_CHAR || *str == SEPARATOR_CHAR)
		return ;
	if (ft_strchr(LABEL_CHARS, *str))
		return ;
	if ((*str == '-' || *str == DIRECT_CHAR) && ft_isdigit(*(str + 1)))
		return ;
	if (*str == DIRECT_CHAR && *(str + 1) == '-' && ft_isdigit(*(str + 2)))
		return ;
	if (*str == LABEL_CHAR && ft_strchr(LABEL_CHARS, *(str + 1)))
		return ;
	if ((*str == DIRECT_CHAR && *(str + 1) == LABEL_CHAR &&
	ft_strchr(LABEL_CHARS, *(str + 2))))
		return ;
	if (*str == COMMENT_CHAR || *str == COMMENT_CHAR_2)
		return ;
	if (ft_isspace(*str))
		return ;
	terminate(info, 0, info->token);
}

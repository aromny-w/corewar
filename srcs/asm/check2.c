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

static bool	is_argument(char type)
{
	if (type == REGISTER || type == DIRECT || type == DIRECT_LABEL ||
	type == INDIRECT || type == INDIRECT_LABEL)
		return (true);
	return (false);
}

static void	instr_check(t_asm *info, t_token **token)
{
	int	i;

	if ((*token)->type == ENDLINE || ((*token)->type == LABEL &&
	(*token = (*token)->next)->type == ENDLINE))
		return ;
	if ((*token)->type != INSTRUCTION)
		terminate(info, 0, *token);
	if (!is_argument(((*token) = (*token)->next)->type))
		terminate(info, 0, *token);
	i = -1;
	while (++i < MAX_ARGS_NUMBER && (*token = (*token)->next)->type != ENDLINE)
	{
		if ((*token)->type != SEPARATOR)
			terminate(info, 0, *token);
		if (!is_argument((*token = (*token)->next)->type))
			terminate(info, 0, *token);
	}
}

static void	header_check(t_asm *info, t_token **token)
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
		//else if ((*token)->type == COMMAND)
		//	terminate(info, 0, *token); // invalid command
		else
			terminate(info, 0, *token);
		if ((*token = (*token)->next)->type != STRING)
			terminate(info, 0, *token);
		if ((*token = (*token)->next)->type != ENDLINE)
			terminate(info, 0, *token);
	}
}

static void	reverse_tokens(t_token **token)
{
	t_token *prev;
	t_token *curr;
	t_token *next;

	prev = NULL;
	curr = *token;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*token = prev;
}

void		syntax_check(t_asm *info)
{
	t_token	*token_ptr;

	reverse_tokens(&info->token);
	token_ptr = info->token;
	header_check(info, &token_ptr);
	while ((token_ptr = token_ptr->next)->type != END)
		instr_check(info, &token_ptr);
}

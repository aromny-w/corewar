/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 19:34:46 by aromny-w          #+#    #+#             */
/*   Updated: 2020/05/06 19:34:47 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	strip_two_endlines(t_exec *info)
{
	t_token	*tptr;
	t_token	*next;

	while ((tptr = info->token)->type == ENDLINE)
	{
		info->token = info->token->next;
		free(tptr->content);
		free(tptr);
	}
	while ((next = tptr->next) && next->next)
	{
		if (next->type == ENDLINE && next->next->type == ENDLINE)
		{
			tptr->next = next->next;
			free(next->content);
			free(next);
		}
		else
			tptr = tptr->next;
	}
}

static void	strip_whitespace(t_exec *info)
{
	t_token	*tptr;
	t_token	*next;

	while ((tptr = info->token)->type == WHITESPACE)
	{
		info->token = info->token->next;
		free(tptr->content);
		free(tptr);
	}
	while ((next = tptr->next))
	{
		if (next->type == WHITESPACE)
		{
			tptr->next = next->next;
			free(next->content);
			free(next);
		}
		else
			tptr = tptr->next;
	}
}

static void	strip_comments(t_exec *info)
{
	t_token	*tptr;
	t_token	*next;

	while ((tptr = info->token)->type == COMMENT)
	{
		info->token = info->token->next;
		free(tptr->content);
		free(tptr);
	}
	while ((next = tptr->next))
	{
		if (next->type == COMMENT)
		{
			tptr->next = next->next;
			free(next->content);
			free(next);
		}
		else
			tptr = tptr->next;
	}
}

void		strip_tokens(t_exec *info)
{
	strip_comments(info);
	strip_whitespace(info);
	strip_two_endlines(info);
}

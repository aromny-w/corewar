/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 19:34:46 by student           #+#    #+#             */
/*   Updated: 2020/05/06 19:34:47 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	strip_two_endlines(t_prog *info)
{
	t_token	*tptr;
	t_token	*next;

	while ((tptr = info->token)->type == ENDLINE)
	{
		info->token = info->token->next;
		free(tptr->str);
		free(tptr);
	}
	while ((next = tptr->next) && next->next)
	{
		if (next->type == ENDLINE && next->next->type == ENDLINE)
		{
			tptr->next = next->next;
			free(next->str);
			free(next);
		}
		else
			tptr = tptr->next;
	}
}

static void	strip_whitespace(t_prog *info)
{
	t_token	*tptr;
	t_token	*next;

	while ((tptr = info->token)->type == WHITESPACE)
	{
		info->token = info->token->next;
		free(tptr->str);
		free(tptr);
	}
	while ((next = tptr->next))
	{
		if (next->type == WHITESPACE)
		{
			tptr->next = next->next;
			free(next->str);
			free(next);
		}
		else
			tptr = tptr->next;
	}
}

static void	strip_comments(t_prog *info)
{
	t_token	*tptr;
	t_token	*next;

	while ((tptr = info->token)->type == COMMENT)
	{
		info->token = info->token->next;
		free(tptr->str);
		free(tptr);
	}
	while ((next = tptr->next))
	{
		if (next->type == COMMENT)
		{
			tptr->next = next->next;
			free(next->str);
			free(next);
		}
		else
			tptr = tptr->next;
	}
}

void		strip_tokens(t_prog *info)
{
	strip_comments(info);
	strip_whitespace(info);
	strip_two_endlines(info);
}

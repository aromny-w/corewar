/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 16:27:31 by student           #+#    #+#             */
/*   Updated: 2020/04/28 16:27:33 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	reverse_instr(t_instr **instr)
{
	t_instr *prev;
	t_instr *curr;
	t_instr *next;

	prev = NULL;
	curr = *instr;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*instr = prev;
}

void	reverse_tokens(t_token **token)
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

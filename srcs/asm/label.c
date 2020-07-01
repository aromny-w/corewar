/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:30:52 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/27 16:30:53 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static bool	is_match(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1++ && *s2++)
		continue ;
	if (*s1 == LABEL_CHAR && !*s2)
		return (true);
	return (false);
}

static void	dereference_label(t_prog *info, t_arg *arg, int pos)
{
	t_line	*lptr;

	lptr = info->line;
	while (lptr)
	{
		if (lptr->label)
			if (is_match(lptr->label->content, arg->ref))
				break ;
		lptr = lptr->next;
	}
	if (!lptr)
		terminate(info, 8, arg->token);
	arg->value = lptr->pos - pos;
}

void		dereference_labels(t_prog *info)
{
	t_line	*lptr;
	int		i;

	lptr = info->line;
	while (lptr)
	{
		i = -1;
		while (lptr->arg[++i].token)
			if (lptr->arg[i].token->type == DIRECT_LABEL ||
			lptr->arg[i].token->type == INDIRECT_LABEL)
				dereference_label(info, &lptr->arg[i], lptr->pos);
		lptr = lptr->next;
	}
}

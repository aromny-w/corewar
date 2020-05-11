/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:07:56 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/05 00:58:41 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	destroy_lines(t_prog *info)
{
	t_line	*tmp;
	t_line	*next;

	tmp = info->line;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

static void	destroy_tokens(t_prog *info)
{
	t_token	*tmp;
	t_token	*next;

	tmp = info->token;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
		tmp = next;
	}
}

void		destroy_struct(t_prog *info)
{
	free(info->filename);
	free(info->buf);
	destroy_tokens(info);
	destroy_lines(info);
}

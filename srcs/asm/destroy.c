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

static void	destroy_instr(t_asm *info)
{
	t_instr	*tmp;
	t_instr	*next;

	tmp = info->instr;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

static void	destroy_tokens(t_asm *info)
{
	t_token	*tmp;
	t_token	*next;

	tmp = info->token;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
		tmp = next;
	}
}

static void	destroy_data(t_asm *info)
{
	size_t	i;

	if (!info->data)
		return ;
	i = -1;
	while (info->data[++i])
	{
		printf("%s\n", info->data[i]);
		free(info->data[i]);
	}
	free(info->data);
}

void		destroy_struct(t_asm *info)
{
	free(info->filename);
	destroy_data(info);
	destroy_tokens(info);
	destroy_instr(info);
}

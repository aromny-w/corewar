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

static void	destroy_instructions(t_asm *info)
{
	if (!info->inst)
		return ;
}

static void	destroy_tokens(t_asm *info)
{
	size_t	i;

	if (!info->token)
		return ;
	i = -1;
	while (++i < info->tokens)
		free(info->token[i].content);
	free(info->token);
}

static void	destroy_data(t_asm *info)
{
	size_t	i;

	if (!info->data)
		return ;
	i = -1;
	while (info->data[++i])
		free(info->data[i]);
	free(info->data);
}

void		destroy_struct(t_asm *info)
{
	free(info->filename);
	destroy_data(info);
	destroy_tokens(info);
	destroy_instructions(info);
}

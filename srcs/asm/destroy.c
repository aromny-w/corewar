/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:07:56 by aromny-w          #+#    #+#             */
/*   Updated: 2020/03/25 17:40:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	destroy_instructions(t_asm *info)
{
	if (!info->inst)
		return ;
	//
}

static void	destroy_tokens(t_asm *info)
{
	size_t	i;

	if (!info->token)
		return ;
	i = -1;
	while (info->token[++i].type != END)
		free(info->token[i].content);
	free(info->token);
}

void		destroy_struct(t_asm *info)
{
	free(info->filename);
	destroy_tokens(info);
	destroy_instructions(info);
}

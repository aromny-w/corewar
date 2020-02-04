/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 22:37:13 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/04 15:11:16 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_struct(t_asm *info, char **input)
{
	ft_bzero(info, sizeof(*info));
	while (*++input)
	{
		if (!ft_strcmp(*input, "-a"))
			info->flag = true;
		else
			info->path = *input;
	}
	info->fd = open(info->path, O_RDONLY);
	info->header.magic = COREWAR_EXEC_MAGIC;
}

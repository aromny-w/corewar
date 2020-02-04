/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:48:33 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/04 18:39:57 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_status(t_asm *info)
{
	size_t	i;

	i = -1;
	ft_printf("%s\n", info->header.prog_name);
	ft_printf("%s\n", info->header.comment);
	while (++i < info->count)
		ft_printf("%s %d\n", info->ops[i].label, info->ops[i].opcode);
}

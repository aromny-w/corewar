/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 21:54:00 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/04 15:11:02 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	terminate(int status, t_asm *info)
{
	destroy_struct(info);
	if (status == -1)
		ft_printf("Can't read source file %s\n", info->path);
	if (status == 0)
		ft_printf("Error\n");
	exit(EXIT_FAILURE);
}

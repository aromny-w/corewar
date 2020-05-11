/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 03:55:26 by student           #+#    #+#             */
/*   Updated: 2020/05/11 03:55:28 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_error(t_prog *info, int status)
{
	if (status == 0)
		ft_dprintf(2, "%s\n", strerror(errno));
	else if (status == 1)
		ft_dprintf(2, "Can't read source file %s.\n", info->path);
	//
}

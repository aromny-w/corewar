/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 21:54:00 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/12 22:46:04 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	terminate(t_asm *info, int status)
{
	if (status == -1)
		ft_dprintf(2, "Can't read source file %s\n", info->path);
	if (status == 0)
		ft_dprintf(2, "Error\n");
	if (status == 1)
		ft_dprintf(2, "Champion name too long (Max length %d)\n",
		PROG_NAME_LENGTH);
	if (status == 2)
		ft_dprintf(2, "Champion comment too long (Max length %d)\n",
		COMMENT_LENGTH);
	destroy_struct(info);
	exit(EXIT_FAILURE);
}

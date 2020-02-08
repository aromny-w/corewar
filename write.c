/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 20:00:35 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/08 21:52:44 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_file(t_asm *info)
{
	char	*name;
	t_byte	test;

	info->fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (write(info->fd, "", 0) == -1)
		terminate(0, info); // write error
	name = ft_strndup(info->path, ft_strlen(info->path) - 2);
	name = ft_strjoin(name, ".cor");
	test.nbr = info->header.magic;
	write(info->fd, test.byte, sizeof(info->header.magic));
}

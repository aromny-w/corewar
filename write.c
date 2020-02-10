/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 20:00:35 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/10 23:55:51 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void					write_file(t_asm *info)
{
	//t_cmd			*op_ptr;
	
	info->fd = open(info->filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (write(info->fd, "", 0) == -1)
		terminate(0, info); // write error
	write(info->fd, info->magic, sizeof(info->header.magic));
	write(info->fd, info->header.prog_name, PROG_NAME_LENGTH);
	write(info->fd, info->header.comment, COMMENT_LENGTH);
	//write(info->fd, test.byte, sizeof(info->header.magic));
}

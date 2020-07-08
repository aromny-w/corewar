/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 20:45:38 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/05 01:18:43 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_buffer(t_exec *info, int fd)
{
	char	*buf;
	int		i;

	i = -1;
	if (!(buf = (char *)malloc(sizeof(char) * (++i + 1))))
		terminate(info, 0, NULL);
	while (read(fd, &buf[i], 1) == 1)
		if (!(buf = (char *)ft_reallocf(buf, sizeof(char) * (++i + 1))))
			terminate(info, 0, NULL);
	buf[i] = '\0';
	return (buf);
}

void		get_file_contents(t_exec *info)
{
	int	fd;

	fd = open(info->path, O_RDONLY);
	if (read(fd, NULL, 0) == -1)
		terminate(info, 1, NULL);
	info->buf = get_buffer(info, fd);
	close(fd);
}

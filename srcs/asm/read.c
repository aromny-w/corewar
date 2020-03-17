/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 20:45:38 by aromny-w          #+#    #+#             */
/*   Updated: 2020/03/17 12:05:20 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	**get_data(t_asm *info)
{
	char	**data;
	int		ret;
	size_t	i;

	i = 0;
	if (!(data = (char **)malloc(sizeof(char *) * (i + 1))))
		terminate(info, -1);
	data[i] = NULL;
	while ((ret = get_next_line(info->fd, &data[i])) == 1)
	{
		if (!(data = (char **)realloc(data, sizeof(char *) * (++i + 1))))
			terminate(info, -1);
		data[i] = NULL;
	}
	if (ret == -1)
		terminate(info, -1);
	return (data);
}

void		read_file(t_asm *info)
{
	info->fd = open(info->path, O_RDONLY);
	if (read(info->fd, 0, 0) == -1)
		terminate(info, -1);
	info->data = get_data(info);
}

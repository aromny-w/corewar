/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 14:58:34 by aromny-w          #+#    #+#             */
/*   Updated: 2019/01/04 16:57:06 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line_realloc(char *old, size_t size)
{
	char *new;

	if (!old)
		return (ft_strnew(size));
	if (!(new = ft_strnew(ft_strlen(old) + size)))
		return (NULL);
	ft_strcpy(new, old);
	ft_strdel(&old);
	return (new);
}

static int	get_line(char **line, char *buff)
{
	char	*nl;
	size_t	len;

	if ((nl = ft_strchr(buff, '\n')))
	{
		if (!(*line = line_realloc(*line, nl - buff)))
			return (-1);
		ft_strncat(*line, buff, nl - buff);
		ft_strncpy(buff, nl + 1, ft_strlen(nl));
	}
	else if ((len = ft_strlen(buff)))
	{
		if (!(*line = line_realloc(*line, len)))
			return (-1);
		ft_strncat(*line, buff, len);
		*buff = '\0';
	}
	return (nl ? 1 : 0);
}

int			get_next_line(int fd, char **line)
{
	static char	buff[FD_SIZE][BUFF_SIZE + 1];
	ssize_t		ret;

	if (read(fd, 0, 0) == -1 || !line)
		return (-1);
	*line = NULL;
	if (get_line(line, buff[fd]))
		return (*line ? 1 : -1);
	while ((ret = read(fd, buff[fd], BUFF_SIZE)) > 0)
	{
		buff[fd][ret] = '\0';
		if (get_line(line, buff[fd]))
			return (*line ? 1 : -1);
	}
	return (*line ? 1 : ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 20:45:38 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/05 01:18:43 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		split_buffer(t_asm *info, char *buf, size_t size)
{
	size_t	start;
	size_t	i;
	size_t	j;

	if (!(info->data = (char **)malloc(sizeof(char *) * (size + 1))))
		terminate(info, 0, NULL);
	i = -1;
	j = -1;
	while (buf[++i])
	{
		start = i;
		while (buf[i] != '\n' && buf[i + 1])
			i++;
		if (!(info->data[++j] = ft_strsub(buf, start, i - start)))
			terminate(info, 0, NULL); // memory error
	}
	info->data[++j] = NULL;
}

static size_t	count_lines(char *str)
{
	size_t	lines;

	lines = 0;
	while (*str)
		if (*str++ == '\n')
			lines++;
	return (lines);
}

static void		read_data(t_asm *info, int fd)
{
	char	*buf;
	ssize_t	ret;
	size_t	i;

	i = 0;
	if (!(buf = (char *)malloc(sizeof(char) * (i + 1))))
		terminate(info, 0, NULL);
	while ((ret = read(fd, &buf[i], 1)) == 1)
		if (!(buf = (char *)ft_reallocf(buf, sizeof(char) * (++i + 1))))
			terminate(info, 0, NULL);
	if (ret == -1)
		terminate(info, 0, NULL); // read error
	if (!*buf || buf[i - 1] != '\n')
		terminate(info, 0, NULL); // syntax error
	split_buffer(info, buf, count_lines(buf));
	free(buf);
}

void			read_file(t_asm *info)
{
	int	fd;

	fd = open(info->path, O_RDONLY);
	if (read(fd, 0, 0) == -1)
		terminate(info, -1, NULL); // read error
	read_data(info, fd);
	close(fd);
}

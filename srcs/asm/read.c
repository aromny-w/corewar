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

static void		strip_comments(t_asm *info)
{
	bool	str;
	size_t	i;
	size_t	j;

	str = false;
	j = -1;
	while (info->data[++j])
	{
		i = -1;
		while (info->data[j][++i])
		{
			if ((info->data[j][i] == COMMENT_CHAR ||
			info->data[j][i] == COMMENT_CHAR_2) && !str)
				info->data[j][i] = '\0';
			if (info->data[j][i] == STRING_CHAR)
				str = !str;
		}
	}
}

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
	i = -1;
	while (info->data[++i])
		printf("%s\n", info->data[i]);
}

static size_t	count_lines(char *buf)
{
	size_t	lines;

	lines = 0;
	while (*buf)
		if (*buf++ == '\n')
			lines++;
	return (lines);
}

static void		read_data(t_asm *info, int fd)
{
	ssize_t	ret;
	size_t	i;

	i = 0;
	if (!(info->buf = (char *)malloc(sizeof(char) * (i + 1))))
		terminate(info, 0, NULL);
	while ((ret = read(fd, &info->buf[i], 1)) == 1)
		if (!(info->buf = (char *)ft_reallocf(info->buf, sizeof(char) *
		(++i + 1))))
			terminate(info, 0, NULL);
	if (ret == -1)
		terminate(info, 0, NULL); // read error
	if (!*info->buf || info->buf[i - 1] != '\n')
		terminate(info, 0, NULL); // syntax error
}

void			read_file(t_asm *info)
{
	int	fd;
	int	i;

	fd = open(info->path, O_RDONLY);
	if (read(fd, 0, 0) == -1)
		terminate(info, -1, NULL); // read error
	read_data(info, fd);
	split_buffer(info, info->buf, count_lines(info->buf));
	strip_comments(info);
	i = -1;
	while (info->data[++i])
		printf("%s\n", info->data[i]);
	close(fd);
}

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

static size_t	count_lines(char *buf)
{
	size_t	lines;

	lines = 0;
	while (*buf)
		if (*buf++ == '\n')
			lines++;
	return (lines);
}

static void		split_buffer(t_prog *info)
{
	size_t	start;
	size_t	size;
	size_t	i;
	size_t	j;

	size = count_lines(info->buf);
	if (!(info->data = (char **)malloc(sizeof(char *) * (size + 1))))
		terminate(info, 0, NULL);
	i = -1;
	j = -1;
	while (++j < size)
	{
		start = ++i;
		while (info->buf[i] != '\n' && info->buf[i + 1])
			i++;
		if (!(info->data[j] = ft_strsub(info->buf, start, i - start)))
			terminate(info, 0, NULL); // memory error
	}
	info->data[j] = NULL;
}

static void		strip_comments(t_prog *info)
{
	bool	comment;
	bool	string;
	size_t	i;
	size_t	j;

	comment = false;
	string = false;
	i = -1;
	j = -1;
	while (info->buf[++i])
	{
		if ((info->buf[i] == COMMENT_CHAR || info->buf[i] == COMMENT_CHAR_2) &&
		string == false)
			comment = true;
		else if (info->buf[i] == '\n' && string == false)
			comment = false;
		else if (info->buf[i] == STRING_CHAR)
			string = !string;
		if (comment == false)
			info->buf[++j] = info->buf[i];
	}
	info->buf[++j] = info->buf[i];
}

static void		read_data(t_prog *info, int fd)
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
	info->buf[i] = '\0';
	if (ret == -1)
		terminate(info, 0, NULL); // read error
}

void			read_file(t_prog *info)
{
	int	fd;

	fd = open(info->path, O_RDONLY);
	if (read(fd, NULL, 0) == -1)
		terminate(info, 1, NULL); // read error
	read_data(info, fd);
	strip_comments(info);
	split_buffer(info);
	close(fd);
}

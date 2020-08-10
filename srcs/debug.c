/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:05:05 by aromny-w          #+#    #+#             */
/*   Updated: 2020/08/03 18:05:10 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "op.h"

char	*buff = "02 90 00 00 00 31 02 04 54 03 02 03 06 64 03 00 "
				"00 08 00 04 09 FF F3 04 54 03 03 03 03 70 01 00 "
				"00 03 70 01 00 00 02 D0 00 64 10 01 00 00 00 00 "
				"09 FF FB";

static void		write_number(int fd, int n, size_t size)
{
	char	byte[4];

	byte[0] = n >> 0;
	byte[1] = n >> 8;
	byte[2] = n >> 16;
	byte[3] = n >> 24;
	if (size >= 4)
		write(fd, &byte[3], sizeof(char));
	if (size >= 3)
		write(fd, &byte[2], sizeof(char));
	if (size >= 2)
		write(fd, &byte[1], sizeof(char));
	if (size >= 1)
		write(fd, &byte[0], sizeof(char));
}

static void		write_code(int fd, size_t size)
{
	while (size--)
		write_number(fd, strtol(buff, &buff, 16), sizeof(char));
}

static void		write_header(int fd, char *name, int size, char *comment)
{
	write_number(fd, COREWAR_EXEC_MAGIC, sizeof(int));
	write(fd, name, PROG_NAME_LENGTH);
	write_number(fd, 0, sizeof(int));
	write_number(fd, size, sizeof(int));
	write(fd, comment, COMMENT_LENGTH);
	write_number(fd, 0, sizeof(int));
}

static size_t	count_bytes(char *str)
{
	size_t	count;

	count = 0;
	while (*str)
		if (*str++ != ' ')
			count++;
	return (count / 2);
}

int				main(void)
{
	int		fd;
	size_t	size;

	fd = open("debug.cor", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (write(fd, NULL, 0) == -1)
		perror(NULL);
	size = count_bytes(buff);
	write_header(fd, "", size, "");
	write_code(fd, size);
	close(fd);
}

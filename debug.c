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
#include <unistd.h>

# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3

typedef struct	s_op
{
	int	opcode;
	int	acb;
	int	arg[4];
}				t_op;

static void	write_op(int fd, t_op op)
{
	write(fd, &op.opcode, sizeof(char));
	write(fd, &op.acb, sizeof(char));
	write(fd, &op.arg[0], sizeof(char));
	write(fd, &op.arg[1], sizeof(char));
	write(fd, &op.arg[2], sizeof(char));
	write(fd, &op.arg[3], sizeof(char));
}

static void	write_number(int fd, int n, size_t size)
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

static void	write_header(int fd, char *name, int size, char *comment)
{
	write_number(fd, COREWAR_EXEC_MAGIC, sizeof(int));
	write(fd, name, PROG_NAME_LENGTH);
	write_number(fd, 0, sizeof(int));
	write_number(fd, size, sizeof(int));
	write(fd, comment, COMMENT_LENGTH);
	write_number(fd, 0, sizeof(int));;
}

// 11 11 11 11 = 0xff
// 11 11 11 10 = 0xfe
// 11 11 11 01 = 0xfd
// 11 11 11 00 = 0xfc
// 11 11 10 00 = 0xf8
// 11 11 01 00 = 0xf4
// 11 11 00 00 = 0xf0
// 11 10 00 00 = 0xe0
// 11 01 00 00 = 0xd0
// 11 00 00 00 = 0xc0
// 10 00 00 00 = 0x80
// 01 00 00 00 = 0x40
// 00 00 00 00 = 0x00


int			main(void)
{
	int		fd;
	t_op	op = {0x02, 0xff, 0xff, 0xff, 0xff, 0xff};

	fd = open("debug.cor", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (write(fd, NULL, 0) == -1)
		perror(NULL);
	write_header(fd, "", 6, "");
	write_op(fd, op);
	close(fd);
}

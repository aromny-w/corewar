/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 22:29:36 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/16 22:29:42 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void		check_filename(char **av, char *filename)
{
	char 	**filename_parts;

	if (!(filename_parts = ft_strsplit(filename, '.')))
		error("Malloc failure.");
	//if (/*rows_count(filename_parts)*/ != 2)
	//	error("Invalid filename.");
	if (!ft_strequ(filename_parts[1], "cor"))
		print_usage(av[0]);
	free_parts(filename_parts); // LIBFT!!
}

static uint8_t	*parse_code(int fd, size_t len)
{
	ssize_t	size;
	uint8_t	*buff;
	int8_t	check;

	if (!(buff = (uint8_t *)ft_memalloc(sizeof(int8_t) * len)))
		error("Malloc failure.");
	size = read(fd, buff, len);
	if (size == -1)
		error("Read failure.");
	if (size < (ssize_t)len || (read(fd, &check, 1) == -1)) //read 1 byte
		error("Invalid file.");
	return (buff);
}

static char		*parse_string(int fd, size_t len)
{
	ssize_t	size;
	char	*buff;

	if (!(buff = ft_strnew(len)))
		error("Malloc failure.");
	size = read(fd, buff, len);
	if (size == -1)
		error("Read failure.");
	if (size < (ssize_t)len)
		error("Invalid file.");
	return (buff);
}

static int32_t	parse_4bytes(int fd)
{
	ssize_t	size;
	uint8_t	val[4];

	size = read(fd, &val, 4);
	if (size == -1)
		error("Read failure.");
	if (size < 4)
		error("Invalid file.");
	return (bin_to_num(val, 4));
}

void			validate_players(char **av, t_game_params *prms)
{
	int fd;
	int i;

	i = -1;
	while (prms->players[++i])
	{
		check_filename(av, prms->players[i]->filename);
		if ((fd = open(prms->players[i]->filename, O_RDONLY)) == -1)
			error("Open failure.");
		if (parse_4bytes(fd) != COREWAR_EXEC_MAGIC)
			error("Invalid magic header.");
		prms->players[i]->name = parse_string(fd, PROG_NAME_LENGTH);
		if (parse_4bytes(fd) != 0)
			error("No null delimeter.");
		if ((prms->players[i]->code_size = parse_4bytes(fd)) > CHAMP_MAX_SIZE)
			error("Too big code size.");
		prms->players[i]->comment = parse_string(fd, COMMENT_LENGTH);
		if (parse_4bytes(fd) != 0)
			error("No null delimeter.");
		prms->players[i]->code = \
			(char *)parse_code(fd, prms->players[i]->code_size);
		close(fd);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:05:05 by malannys          #+#    #+#             */
/*   Updated: 2020/08/03 18:05:10 by malannys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

static void		write_args(int fd, t_instruction *instr)
{
	size_t	i;

	i = 0;
	while (i < (size_t)instr->op.params)
	{
		if (instr->arg_type[i] == REG_CODE)
			ft_putchar_fd(REG_CHAR, fd);
		else if (instr->arg_type[i] == DIR_CODE)
			ft_putchar_fd(DIRECT_CHAR, fd);
		ft_putnbr_fd(instr->arg_val[i], fd);
		if (i != (size_t)instr->op.params - 1)
		{
			ft_putchar_fd(SEPARATOR_CHAR, fd);
			ft_putchar_fd(' ', fd);
		}
		i++;
	}
}

static char		*change_extension(char *filename)
{
	char	*res;
	char	*tmp;

	if (!(tmp = ft_strndup(filename, ft_strlen(filename) - 4)))
		error("Malloc failure.");
	if (!(res = ft_strjoin(tmp, ".s")))
		error("Malloc failure.");
	free(tmp);
	return (res);
}

static void		write_asm1(t_instruction *tmp, \
								int fd, char *filename)
{
	while (tmp)
	{
		ft_putstr_fd(tmp->op.name, fd);
		ft_putstr_fd(" ", fd);
		write_args(fd, tmp);
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
	}
	free(filename);
	close(fd);
}

void			write_asm(t_bin *bin)
{
	int				fd;
	char			*filename;
	t_instruction	*tmp;

	tmp = bin->instr;
	filename = change_extension(bin->filename);
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		error("Open failure.");
	ft_printf("Writing output program to %s.\n", filename);
	ft_putstr_fd(NAME_CMD_STRING, fd);
	ft_putstr_fd(" \"", fd);
	ft_putstr_fd(bin->prog_name, fd);
	ft_putstr_fd("\"\n", fd);
	ft_putstr_fd(COMMENT_CMD_STRING, fd);
	ft_putstr_fd(" \"", fd);
	ft_putstr_fd(bin->comment, fd);
	ft_putstr_fd("\"\n\n", fd);
	write_asm1(tmp, fd, filename);
}

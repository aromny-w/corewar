#include "disasm.h"

static void		write_args(int fd, t_instruction *instr)
{
	size_t	i;

	i = 0;
	while (instr->arg_type[i])
	{
		/* if (i)
			ft_dprintf(fd, "%c ", SEPARATOR_CHAR);
		if (instr->arg_type[i] == T_REG)
			ft_dprintf(fd, "%c", REG_CHAR);
		else if (instr->arg_type[i] == T_DIR)
			ft_dprintf(fd, "%c", DIRECT_CHAR);
		ft_dprintf(fd, "%ld", instr->arg_val[i]); */
		if (i)
		{
			ft_putchar_fd(SEPARATOR_CHAR, fd);
			write(2, " ", 1);
		}
		if (instr->arg_type[i] == T_REG)
			ft_putchar_fd(REG_CHAR, fd);
		else if (instr->arg_type[i] == T_DIR)
			ft_putchar_fd(DIRECT_CHAR, fd);
		ft_putnbr_fd(instr->arg_val[i], fd);
		i++;
	}

}

static char		*change_extension(char *filename)
{
	char    **filename_parts;
	char	*res;

	if (!(filename_parts = ft_strsplit(filename, '.')))
		error("Malloc failure.");
	if (!(res = ft_strjoin(filename_parts[0], ".s")))
		error("Malloc failure.");
	/*ft_arrdel(&filename_parts);*/ // LIBFT!!
	return (res);
}

void			write_asm(t_bin *bin)
{
	int				fd;
	char			*filename;
	t_instruction	*tmp;

	tmp = bin->instr;
	filename = change_extension(bin->filename);
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC)) == -1)
		error("Open failure.");
/* 	ft_dprintf(fd, "%s \"%s\"\n", NAME_CMD_STRING, bin->prog_name);
	ft_dprintf(fd, "%s \"%s\"\n\n", COMMENT_CMD_STRING, bin->comment);
	while (tmp)
	{
		ft_dprintf(fd, "%s ", tmp->op.name);
		write_args(fd, tmp);
		ft_dprintf(fd, "\n");
		tmp = tmp->next;
	} */
	ft_putstr_fd(NAME_CMD_STRING, fd);
	ft_putstr_fd(" \"", fd);
	ft_putstr_fd(bin->prog_name, fd);
	ft_putstr_fd("\"\n", fd);
	ft_putstr_fd(COMMENT_CMD_STRING, fd);
	ft_putstr_fd(" \"", fd);
	ft_putstr_fd(bin->comment, fd);
	ft_putstr_fd("\"\n\n", fd);
	ft_putstr_fd("In process...\n", fd);
	while (tmp)
	{
		ft_putstr_fd(" ", fd);
		ft_putstr_fd(tmp->op.name, fd);
		write_args(fd, tmp);
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
	}
	close(fd);
}
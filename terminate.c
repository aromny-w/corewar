/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 21:54:00 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/15 21:21:05 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	lexical_error(t_asm *info, int status)
{
	if (status == 21)
		ft_dprintf(2, "Lexical error at [%d:%d]\n", info->lines,
		info->index + 1);
}

static void	syntax_error(t_asm *info, int status)
{
	size_t	i;

	i = 0;
	while (info->line[info->index + i] &&
	!ft_isspace(info->line[info->index + i]))
		i++;
	if (status == 11)
		ft_dprintf(2, "Syntax error at token [TOKEN][%.3d:%.3d] %s \"%s\"\n",
		info->lines, info->index + 1, "COMMAND_COMMENT", COMMENT_CMD_STRING);
	if (status == 12)
		ft_dprintf(2, "Syntax error at token [TOKEN][%.3d:%.3d] %s \"%s\"\n",
		info->lines, info->index + 1, "COMMAND_NAME", NAME_CMD_STRING);
	if (status == 13)
		ft_dprintf(2, "Syntax error at token [TOKEN][%.3d:%.3d] %s \"%.*s\"\n",
		info->lines, info->index + 1, "INSTRUCTION", i,
		&info->line[info->index]);
}

static void	header_error(t_asm *info, int status)
{
	(void)info;
	if (status == 1)
		ft_dprintf(2, "Champion name too long (Max length %d)\n",
		PROG_NAME_LENGTH);
	if (status == 2)
		ft_dprintf(2, "Champion comment too long (Max length %d)\n",
		COMMENT_LENGTH);
}

void		terminate(t_asm *info, int status)
{
	if (status == -1)
		ft_dprintf(2, "Can't read source file %s\n", info->path);
	if (status == 0)
		ft_dprintf(2, "Error\n");
	if (status >= 1 && status <= 10)
		header_error(info, status);
	if (status >= 11 && status <= 20)
		syntax_error(info, status);
	if (status >= 21 && status <= 30)
		lexical_error(info, status);
	destroy_struct(info);
	exit(EXIT_FAILURE);
}

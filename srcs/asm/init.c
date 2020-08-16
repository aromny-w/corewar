/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 22:37:13 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/01 20:24:29 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_filename(char *path)
{
	char	*name;
	char	*start;
	char	*end;
	char	*dot;

	if (!path || !*path)
		return (ft_strdup(".cor"));
	end = path + ft_strlen(path) - 1;
	while (end > path && *end == '/')
		end--;
	if (end == path && *end == '/')
		return (ft_strdup("/.cor"));
	start = end;
	while (start > path && *(start - 1) != '/')
		start--;
	if ((dot = ft_strrchr(start, '.')) && dot != start)
		end = dot - 1;
	if (!(name = ft_strndup(path, end - path + 1 + 4)))
		return (NULL);
	ft_strcpy(name + (end - path + 1), ".cor");
	return (name);
}

void		get_options(t_exec *info, char **input)
{
	ft_bzero(info, sizeof(*info));
	info->header.magic = COREWAR_EXEC_MAGIC;
	while (*++input)
	{
		if (!ft_strcmp(*input, "-a"))
			info->option = true;
		else
			info->path = *input;
	}
	if (!(info->filename = get_filename(info->path)))
		terminate(info, 0, NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 22:37:13 by aromny-w          #+#    #+#             */
/*   Updated: 2020/04/01 20:24:29 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_filename(t_prog *info)
{
	char	*str;
	char	*s1;
	char	*s2;
	size_t	len;

	s1 = ft_strrchr(info->path, '.');
	s2 = ft_strrchr(info->path, '/');
	len = ft_strlen(info->path);
	if ((s1 && (!s2 || (s1 = ft_strrchr(s2, '.')))))
		len -= ft_strlen(s1);
	if (!(str = ft_strnew(len + 4)))
		terminate(info, 0, NULL);
	ft_strncpy(str, info->path, len);
	ft_strcat(str, ".cor");
	return (str);
}

void		get_options(t_prog *info, char **input)
{
	ft_bzero(info, sizeof(*info));
	while (*++input)
	{
		if (!ft_strcmp(*input, "-a"))
			info->option = true;
		else
			info->path = *input;
	}
	info->filename = get_filename(info);
}

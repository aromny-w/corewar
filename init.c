/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 22:37:13 by aromny-w          #+#    #+#             */
/*   Updated: 2020/02/10 23:54:26 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned char	*get_magic(t_asm *info)
{
	unsigned char	*str;
	t_byte			value;
	unsigned char	i;
	unsigned char	j;

	if (!(str = (unsigned char *)malloc(sizeof(unsigned char) *
	sizeof(info->header.magic))))
		terminate(0, info); // memory error
	value.nbr = info->header.magic;
	i = 0;
	j = sizeof(value.nbr);
	while (i < sizeof(value.nbr))
		str[i++] = value.byte[--j];
	return (str);
}

static char				*get_filename(t_asm *info)
{
	char	*str;
	size_t	len;

	len = ft_strlen(info->path);
	if (ft_strcmp(info->path + len - 2, ".s"))
		terminate(0, info);  //invalid extension
	if (!(str = ft_strnew(len + 2)))
		terminate(0, info); // memory error
	ft_strncpy(str, info->path, len - 2);
	ft_strcat(str, ".cor");
	return (str);
}

void					init_struct(t_asm *info, char **input)
{
	ft_bzero(info, sizeof(*info));
	while (*++input)
	{
		if (!ft_strcmp(*input, "-a"))
			info->flag = true;
		else
			info->path = *input;
	}
	info->filename = get_filename(info);
	info->header.magic = COREWAR_EXEC_MAGIC;
	info->magic = get_magic(info);
}

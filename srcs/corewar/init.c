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

#include "corewar.h"

void	get_options(t_prog *info, char **input)
{
	ft_bzero(info, sizeof(*info));
	while (*++input)
	{
		if (!ft_strcmp(*input, "-dump"))
		{
			info->dump.option = true;
			if (*(input + 1))
				info->dump.n = ft_atoi(*++input);
		}
		else if (!ft_strcmp(*input, "-n"))
		{
			info->n.option = true;
			if (*(input + 1))
				info->n.n = ft_atoi(*++input);
		}
		else
			info->path = *input;
	}
}

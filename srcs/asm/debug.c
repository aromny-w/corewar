/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <aromny-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 23:30:32 by student           #+#    #+#             */
/*   Updated: 2020/04/04 17:46:33 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_types(t_asm *info)
{
	size_t	i;

	i = -1;
	while (++i < info->tokens)
		ft_printf("%s\n", g_type[info->token[i].type]);
}

static void	print_tokens(t_asm *info)
{
	size_t	i;

	i = -1;
	while (++i < info->tokens)
	{
		if (info->token[i].type == ENDLINE || info->token[i].type == END)
			ft_printf("\n");
		else
			ft_printf("%s", info->token[i].content);
		if (info->token[i].type != ENDLINE && info->token[i].type != END &&
		info->token[i + 1].type != ENDLINE && info->token[i + 1].type != END &&
		info->token[i + 1].type != SEPARATOR)
			ft_printf(" ");
	}
}

static void	print_data(t_asm *info)
{
	size_t	i;

	i = -1;
	while (info->data[++i])
		ft_printf("%s\n", info->data[i]);
	ft_printf("%s\n", info->data[i]);
}

void		debug(t_asm *info)
{
	bool	flag[3] = { 1, 0, 0 };

	if (flag[0] == true)
		print_data(info);
	if (flag[1] == true)
		print_tokens(info);
	if (flag[2] == true)
		print_types(info);
}

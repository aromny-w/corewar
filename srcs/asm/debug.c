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
	t_token	*tptr;

	tptr = info->token;
	while (tptr)
	{
		ft_printf("%s\n", g_type[tptr->type]);
		tptr = tptr->next;
	}
}

static void	print_tokens(t_asm *info)
{
	t_token	*tptr;

	tptr = info->token;
	while (tptr->type != END)
	{
		ft_printf("%s", tptr->content ? tptr->content : "\n");
		if (tptr->type != ENDLINE && tptr->next->type != ENDLINE &&
		tptr->next->type != END && tptr->next->type != SEPARATOR)
			ft_printf(" ");
		tptr = tptr->next;
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
	bool	flag[3];

	flag[0] = false;
	flag[1] = true;
	flag[2] = false;
	if (flag[0] == true)
		print_data(info);
	if (flag[1] == true)
		print_tokens(info);
	if (flag[2] == true)
		print_types(info);
}

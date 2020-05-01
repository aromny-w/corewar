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

static void	print_instr(t_instr *instr)
{
	if (!instr)
		return ;
	//
}

static void	print_tokens(t_token *token)
{
	if (!token)
		return ;
	while (token->type != END)
	{
		ft_printf("[TOKEN] %-15s \"%-14s\", [%.3d:%.3d]\n", g_type[token->type],
		token->content, token->row, token->col);
		token = token->next;
	}
}

static void	print_data(char **data)
{
	size_t	i;

	if (!data)
		return ;
	i = -1;
	while (data[++i])
		ft_printf("%s\n", data[i]);
	ft_printf("%s\n", data[i]);
}

void		debug(t_prog *info, bool data, bool token, bool instr)
{
	if (data == true)
		print_data(info->data);
	if (token == true)
		print_tokens(info->token);
	if (instr == true)
		print_instr(info->instr);
}

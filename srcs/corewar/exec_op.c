/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 20:51:21 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/29 21:41:53 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		validate_argcode(t_carriage *carriage, int code)
{
	int i;
	int arg_type;
	int valid;
	int skip;

	valid = 1;
	skip = 0;
	i = -1;
	while (++i < g_op_tab[carriage->code_op - 1].params)
	{
		arg_type = code >> (8 - (i + 1) * 2) & 3;
		if (!arg_type && g_op_tab[carriage->code_op - 1].type[i])
			valid = 0;
		if (!arg_type)
			continue ;
		if (!(g_op_tab[carriage->code_op - 1].type[i] & (1 << (arg_type - 1))))
			valid = 0;
		if (arg_type == DIR_CODE)
			skip += g_op_tab[carriage->code_op - 1].idx ? IND_SIZE : DIR_SIZE;
		else
			skip += arg_type == IND_CODE ? IND_SIZE : sizeof(char);
	}
	if (!valid)
		carriage->bytes_next_op += skip;
	return (valid);
}

void	exec_op(t_carriage *carriage, t_game_params *params)
{
	int		arg_code;

	carriage->bytes_next_op = 1;
	if (carriage->code_op > 16 || carriage->code_op < 1)
		return ;
	arg_code = 0;
	if (g_op_tab[carriage->code_op - 1].pcode)
	{
		arg_code = arena_read_byte(params->arena, carriage->cur_position +
					carriage->bytes_next_op);
		carriage->bytes_next_op++;
		if (!validate_argcode(carriage, arg_code))
			return ;
	}
	(*g_execs[carriage->code_op - 1])(carriage, params, arg_code);
}

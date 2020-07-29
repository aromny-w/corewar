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

#include "vm.h"

int		validate_argcode(t_carriage *carriage, int code)
{
	int i;
	int arg_type;
	int valid;
	int skip;

	valid = 1;
	skip = 0;
	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		arg_type = (code >> (MAX_ARGS_NUMBER - 1 - i) * 2) & 0x03;
		if (!arg_type && (g_op_tab[carriage->code_op - 1].type[i]))
			valid = 0;
		if (!arg_type)
			break ;
		if (!(g_op_tab[carriage->code_op - 1].type[i] & (1 << (arg_type - 1))))
			valid = 0;
		if (arg_type == DIR_CODE)
			skip += (g_op_tab[carriage->code_op - 1].idx ? IND_SIZE : DIR_SIZE);
		else
			skip += arg_type == IND_CODE ? IND_SIZE : 1;
		i++;
	}
	if (!valid)
		carriage->bytes_next_op += skip;
	return (valid);
}

void	exec_op(t_carriage *carriage, t_game_params *params)
{
	int		arg_code;
	int		argc_valid;

	carriage->bytes_next_op = 1;
	if (carriage->code_op > 16 || carriage->code_op < 1)
		return ;
	arg_code = 0;
	if (g_op_tab[carriage->code_op - 1].pcode)
	{
		arg_code = arena_read_byte(params->arena, carriage->cur_position +
					carriage->bytes_next_op);
		carriage->bytes_next_op++;
		argc_valid = validate_argcode(carriage, arg_code);
		if (!argc_valid)
			return ;
	}
	(*g_execs[carriage->code_op - 1])(carriage, params, arg_code);
}

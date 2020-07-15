/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 21:42:07 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/15 22:15:21 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void op_st(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int		args[2];
	int		arg2_type;

	arg2_type = (arg_code >> 4) & 3;
	args[0] = get_argument(params->arena, carriage, T_REG, 0);
	if (arg2_type == T_REG)
		save_registry(carriage, arena_read_byte(params->arena,
				carriage->cur_position + carriage->bytes_next_op), args[0]);
	else
	{
		args[1] = read_number(params->arena, carriage->cur_position +
			carriage->bytes_next_op, IND_SIZE) % IDX_MOD;
		write_number(params->arena, carriage->cur_position + args[1], REG_SIZE,
				args[0]);
	}
}


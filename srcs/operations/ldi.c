/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 22:49:45 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/15 22:54:47 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void op_ldi(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int		args[3];

	args[0] = get_argument(params->arena, carriage, (arg_code >> 6) & 3, 0);
	args[1] = get_argument(params->arena, carriage, (arg_code >> 4) & 3, 0);
	args[2] = arena_read_byte(params->arena, carriage->cur_position +
													carriage->bytes_next_op);

	save_registry(carriage, args[2], read_number(params->arena,
		carriage->cur_position + ((args[0] + args[1]) % IDX_MOD), REG_SIZE));
}

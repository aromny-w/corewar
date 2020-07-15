/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 23:22:21 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/15 23:25:25 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void op_lldi(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int		args[3];
	int		value;

	args[0] = get_argument(params->arena, carriage, (arg_code >> 6) & 3, 0);
	args[1] = get_argument(params->arena, carriage, (arg_code >> 4) & 3, 0);
	args[2] = arena_read_byte(params->arena, carriage->cur_position +
													carriage->bytes_next_op);
	value = read_number(params->arena,
		carriage->cur_position + args[0] + args[1], REG_SIZE);
	save_registry(carriage, args[2], value);
	carriage->carry = value ? 0 : 1;
}

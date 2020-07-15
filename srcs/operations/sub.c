/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 22:30:57 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/15 22:37:58 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void op_sub(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int		args[3];

	args[0] = get_argument(params->arena, carriage, T_REG, 0);
	args[1] = get_argument(params->arena, carriage, T_REG, 0);
	args[2] = arena_read_byte(params->arena, carriage->cur_position +
												carriage->bytes_next_op);
	save_registry(carriage, args[2], args[0] - args[1]);
	carriage->carry = args[0] - args[1] ? 0 : 1;
	(void)arg_code;
}


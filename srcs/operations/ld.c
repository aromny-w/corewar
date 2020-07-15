/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 21:15:04 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/15 22:36:34 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void op_ld(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int		args[2];
	int		arg_type;

	arg_type = (arg_code >> 6) & 3;
	args[0] = get_argument(params->arena, carriage, arg_type, 0);
	args[1] = arena_read_byte(params->arena, carriage->cur_position + 
			carriage->bytes_next_op);
	save_registry(carriage, args[1], args[0]);
	carriage->carry = args[0] ? 0 : 1;
}

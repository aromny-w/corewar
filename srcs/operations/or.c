/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 22:32:30 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/15 22:37:02 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void op_or(t_carriage *carriage, t_game_params *params, int arg_code)
{
	int		args[3];
	int		arg_type;
	int		res;

	arg_type = (arg_code >> 6) & 3;
	args[0] = get_argument(params->arena, carriage, arg_type, 0);
	arg_type = (arg_code >> 4) & 3;
	args[1] = get_argument(params->arena, carriage, arg_type, 0);
	args[2] = arena_read_byte(params->arena, carriage->cur_position +
												carriage->bytes_next_op);
	res = args[0] | args[1];
	save_registry(carriage, args[2], res);
	carriage->carry = res ? 0 : 1;
}
